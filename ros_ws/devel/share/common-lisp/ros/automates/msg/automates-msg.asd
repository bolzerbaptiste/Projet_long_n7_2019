
(cl:in-package :asdf)

(defsystem "automates-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Entrees" :depends-on ("_package_Entrees"))
    (:file "_package_Entrees" :depends-on ("_package"))
    (:file "Sorties" :depends-on ("_package_Sorties"))
    (:file "_package_Sorties" :depends-on ("_package"))
  ))