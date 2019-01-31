
(cl:in-package :asdf)

(defsystem "shuttles-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "srvGetEmptyShuttles" :depends-on ("_package_srvGetEmptyShuttles"))
    (:file "_package_srvGetEmptyShuttles" :depends-on ("_package"))
    (:file "srvGetShuttleStatus" :depends-on ("_package_srvGetShuttleStatus"))
    (:file "_package_srvGetShuttleStatus" :depends-on ("_package"))
  ))