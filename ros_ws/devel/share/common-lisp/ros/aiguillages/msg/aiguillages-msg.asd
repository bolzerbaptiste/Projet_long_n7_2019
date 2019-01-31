
(cl:in-package :asdf)

(defsystem "aiguillages-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "ExchangeSh" :depends-on ("_package_ExchangeSh"))
    (:file "_package_ExchangeSh" :depends-on ("_package"))
    (:file "Actionneurs" :depends-on ("_package_Actionneurs"))
    (:file "_package_Actionneurs" :depends-on ("_package"))
    (:file "Capteurs" :depends-on ("_package_Capteurs"))
    (:file "_package_Capteurs" :depends-on ("_package"))
  ))