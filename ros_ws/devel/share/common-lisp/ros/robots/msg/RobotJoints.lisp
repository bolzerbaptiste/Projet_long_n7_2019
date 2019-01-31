; Auto-generated. Do not edit!


(cl:in-package robots-msg)


;//! \htmlinclude RobotJoints.msg.html

(cl:defclass <RobotJoints> (roslisp-msg-protocol:ros-message)
  ((joint1
    :reader joint1
    :initarg :joint1
    :type cl:integer
    :initform 0)
   (joint2
    :reader joint2
    :initarg :joint2
    :type cl:integer
    :initform 0)
   (joint3
    :reader joint3
    :initarg :joint3
    :type cl:integer
    :initform 0)
   (joint4
    :reader joint4
    :initarg :joint4
    :type cl:integer
    :initform 0)
   (joint5
    :reader joint5
    :initarg :joint5
    :type cl:integer
    :initform 0)
   (joint6
    :reader joint6
    :initarg :joint6
    :type cl:integer
    :initform 0)
   (joint7
    :reader joint7
    :initarg :joint7
    :type cl:integer
    :initform 0))
)

(cl:defclass RobotJoints (<RobotJoints>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <RobotJoints>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'RobotJoints)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name robots-msg:<RobotJoints> is deprecated: use robots-msg:RobotJoints instead.")))

(cl:ensure-generic-function 'joint1-val :lambda-list '(m))
(cl:defmethod joint1-val ((m <RobotJoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robots-msg:joint1-val is deprecated.  Use robots-msg:joint1 instead.")
  (joint1 m))

(cl:ensure-generic-function 'joint2-val :lambda-list '(m))
(cl:defmethod joint2-val ((m <RobotJoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robots-msg:joint2-val is deprecated.  Use robots-msg:joint2 instead.")
  (joint2 m))

(cl:ensure-generic-function 'joint3-val :lambda-list '(m))
(cl:defmethod joint3-val ((m <RobotJoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robots-msg:joint3-val is deprecated.  Use robots-msg:joint3 instead.")
  (joint3 m))

(cl:ensure-generic-function 'joint4-val :lambda-list '(m))
(cl:defmethod joint4-val ((m <RobotJoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robots-msg:joint4-val is deprecated.  Use robots-msg:joint4 instead.")
  (joint4 m))

(cl:ensure-generic-function 'joint5-val :lambda-list '(m))
(cl:defmethod joint5-val ((m <RobotJoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robots-msg:joint5-val is deprecated.  Use robots-msg:joint5 instead.")
  (joint5 m))

(cl:ensure-generic-function 'joint6-val :lambda-list '(m))
(cl:defmethod joint6-val ((m <RobotJoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robots-msg:joint6-val is deprecated.  Use robots-msg:joint6 instead.")
  (joint6 m))

(cl:ensure-generic-function 'joint7-val :lambda-list '(m))
(cl:defmethod joint7-val ((m <RobotJoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robots-msg:joint7-val is deprecated.  Use robots-msg:joint7 instead.")
  (joint7 m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <RobotJoints>) ostream)
  "Serializes a message object of type '<RobotJoints>"
  (cl:let* ((signed (cl:slot-value msg 'joint1)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'joint2)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'joint3)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'joint4)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'joint5)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'joint6)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'joint7)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <RobotJoints>) istream)
  "Deserializes a message object of type '<RobotJoints>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'joint1) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'joint2) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'joint3) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'joint4) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'joint5) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'joint6) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'joint7) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<RobotJoints>)))
  "Returns string type for a message object of type '<RobotJoints>"
  "robots/RobotJoints")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RobotJoints)))
  "Returns string type for a message object of type 'RobotJoints"
  "robots/RobotJoints")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<RobotJoints>)))
  "Returns md5sum for a message object of type '<RobotJoints>"
  "5e5a38d7bec96b3437eca1b49cd93693")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'RobotJoints)))
  "Returns md5sum for a message object of type 'RobotJoints"
  "5e5a38d7bec96b3437eca1b49cd93693")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<RobotJoints>)))
  "Returns full string definition for message of type '<RobotJoints>"
  (cl:format cl:nil "int32 joint1~%int32 joint2~%int32 joint3~%int32 joint4~%int32 joint5~%int32 joint6~%int32 joint7~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'RobotJoints)))
  "Returns full string definition for message of type 'RobotJoints"
  (cl:format cl:nil "int32 joint1~%int32 joint2~%int32 joint3~%int32 joint4~%int32 joint5~%int32 joint6~%int32 joint7~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <RobotJoints>))
  (cl:+ 0
     4
     4
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <RobotJoints>))
  "Converts a ROS message object to a list"
  (cl:list 'RobotJoints
    (cl:cons ':joint1 (joint1 msg))
    (cl:cons ':joint2 (joint2 msg))
    (cl:cons ':joint3 (joint3 msg))
    (cl:cons ':joint4 (joint4 msg))
    (cl:cons ':joint5 (joint5 msg))
    (cl:cons ':joint6 (joint6 msg))
    (cl:cons ':joint7 (joint7 msg))
))
