
(cl:in-package :asdf)

(defsystem "shuttles-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "msgShuttleCreate" :depends-on ("_package_msgShuttleCreate"))
    (:file "_package_msgShuttleCreate" :depends-on ("_package"))
    (:file "msgShuttleChange" :depends-on ("_package_msgShuttleChange"))
    (:file "_package_msgShuttleChange" :depends-on ("_package"))
  ))