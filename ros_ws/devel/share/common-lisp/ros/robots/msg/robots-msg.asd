
(cl:in-package :asdf)

(defsystem "robots-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "RobotJoints" :depends-on ("_package_RobotJoints"))
    (:file "_package_RobotJoints" :depends-on ("_package"))
    (:file "MoveRobot" :depends-on ("_package_MoveRobot"))
    (:file "_package_MoveRobot" :depends-on ("_package"))
  ))