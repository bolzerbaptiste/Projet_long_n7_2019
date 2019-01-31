
(cl:in-package :asdf)

(defsystem "commande-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Actionneurs" :depends-on ("_package_Actionneurs"))
    (:file "_package_Actionneurs" :depends-on ("_package"))
    (:file "Capteurs" :depends-on ("_package_Capteurs"))
    (:file "_package_Capteurs" :depends-on ("_package"))
  ))