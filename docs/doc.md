# Tagesjournale

# Code 


## SQLI

    const auto statement = "INSERT into users(uuid, email, name, password) VALUES ('" +
                            W.esc(user.get_uuid()) + "', '" + W.esc(user.get_email()) + "', '" + W.esc(user.get_name()) +
                            "', '" + W.esc(user.get_password()) + "')";
 
Man sieht hier, wie alle Values escaped wurden. Man hätte das schöner mit einem StringBuilder machen können, aber habe ich aus Zeitgründen nicht gemacht.

## Hashing

Das Passwort wird so schnell wie möglich aus dem Arbeitsspeicher entfernt, indem es mit dem gehashten Passwort (via Bcrypt) überschrieben wird. Passiert in dem Moment, in dem die Daten ins Model geladen werden.
`password = bcrypt::generateHash(password, 10);`
                            
Das Passwort wird dann mit der folgen Funktion überprüft (beim Login)


    bool user_model::validate_password(std::string password) {
        return bcrypt::validatePassword(password, this->get_password());
    }


## Logger

Ich habe mir einen sehr kleinen Logger geschrieben, der in die Datei log.log (oder was auch immer spezifiziert wird) logs schreibt.

Die Datei sieht in etwa so aus:\
\
[Tue Jan 19 22:49:51 2021]: Get User:dominic.jaermann@sbb.ch\
[Tue Jan 19 22:50:29 2021]: Startet application\
[Tue Jan 19 22:50:32 2021]: Get User:dominic.jaermann@sbb.ch\
[Tue Jan 19 22:50:40 2021]: Get User:dominic.jaermann@sbb.ch\
[Tue Jan 19 22:50:40 2021]: successful login attempt with email  :dominic.jaermann@sbb.ch\
[Tue Jan 19 22:50:40 2021]: Generate JWT for user:  :dominic.jaermann@sbb.ch\

## XSS

Ich habe bei Angular zu Testzwecken einen eingenen Sanitizer geschrieben. Er ist aber nur für HTML anwendbar und bei allem andere würde er nicht funktionieren.


      const temp = document.createElement('div');
      temp.textContent = this.unsafeUser;
      this.element.nativeElement.innerHTML = temp.innerHTML;


Die Idee ist: Das man in ein Div den TextContent setzt von dem String den man escaped haben will und danach das InnerHTML holt und dann einfügt. Da sind dann alle Html Elemente und Tags entfernt.

## Session Handling

Die Applikation implementiert JSONWebTokens mit dem Bearer Token. Das ganze Crypto Zeug macht eine Library aber der Rest (parsen, etc) kommt von mir.

Hier wird z.B der User vom JWT gefetched

    user_model *user_service::get_user_from_jwt(std::string jwt) {
        auto dec_obj = jwt::decode(jwt, algorithms({"HS256"}), secret(SECRET));
        const auto email = dec_obj.payload().create_json_obj().at("user");
        return user_service::get_user(email);
    }

Hier wird der User in das Token gespeichert und signiert.

    std::string *user_service::generate_jwt(user_model *user) {
        jwt::jwt_object obj{algorithm("HS256"), secret(SECRET), payload({{"user", user->get_email()}})};
        logger::get_instance()->log("Generate JWT for user:  :" + user->get_email(), LogSeverity::Normal);
        return new std::string(obj.signature().c_str());
    }
    