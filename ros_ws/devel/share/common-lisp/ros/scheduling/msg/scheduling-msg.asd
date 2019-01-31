
(cl:in-package :asdf)

(defsystem "scheduling-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "Msg_LoadShuttle" :depends-on ("_package_Msg_LoadShuttle"))
    (:file "_package_Msg_LoadShuttle" :depends-on ("_package"))
  ))