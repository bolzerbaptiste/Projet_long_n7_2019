
(cl:in-package :asdf)

(defsystem "commande_locale-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "Msg_PinControl" :depends-on ("_package_Msg_PinControl"))
    (:file "_package_Msg_PinControl" :depends-on ("_package"))
    (:file "Msg_SensorState" :depends-on ("_package_Msg_SensorState"))
    (:file "_package_Msg_SensorState" :depends-on ("_package"))
    (:file "Msg_SwitchControl" :depends-on ("_package_Msg_SwitchControl"))
    (:file "_package_Msg_SwitchControl" :depends-on ("_package"))
    (:file "Msg_StopControl" :depends-on ("_package_Msg_StopControl"))
    (:file "_package_Msg_StopControl" :depends-on ("_package"))
    (:file "Msg_Color" :depends-on ("_package_Msg_Color"))
    (:file "_package_Msg_Color" :depends-on ("_package"))
  ))