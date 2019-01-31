; Auto-generated. Do not edit!


(cl:in-package robots-msg)


;//! \htmlinclude MoveRobot.msg.html

(cl:defclass <MoveRobot> (roslisp-msg-protocol:ros-message)
  ((position
    :reader position
    :initarg :position
    :type cl:integer
    :initform 0)
   (bras
    :reader bras
    :initarg :bras
    :type cl:integer
    :initform 0)
   (pince
    :reader pince
    :initarg :pince
    :type cl:integer
    :initform 0))
)

(cl:defclass MoveRobot (<MoveRobot>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MoveRobot>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MoveRobot)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name robots-msg:<MoveRobot> is deprecated: use robots-msg:MoveRobot instead.")))

(cl:ensure-generic-function 'position-val :lambda-list '(m))
(cl:defmethod position-val ((m <MoveRobot>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robots-msg:position-val is deprecated.  Use robots-msg:position instead.")
  (position m))

(cl:ensure-generic-function 'bras-val :lambda-list '(m))
(cl:defmethod bras-val ((m <MoveRobot>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robots-msg:bras-val is deprecated.  Use robots-msg:bras instead.")
  (bras m))

(cl:ensure-generic-function 'pince-val :lambda-list '(m))
(cl:defmethod pince-val ((m <MoveRobot>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robots-msg:pince-val is deprecated.  Use robots-msg:pince instead.")
  (pince m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MoveRobot>) ostream)
  "Serializes a message object of type '<MoveRobot>"
  (cl:let* ((signed (cl:slot-value msg 'position)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'bras)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'pince)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MoveRobot>) istream)
  "Deserializes a message object of type '<MoveRobot>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'position) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'bras) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'pince) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MoveRobot>)))
  "Returns string type for a message object of type '<MoveRobot>"
  "robots/MoveRobot")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MoveRobot)))
  "Returns string type for a message object of type 'MoveRobot"
  "robots/MoveRobot")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MoveRobot>)))
  "Returns md5sum for a message object of type '<MoveRobot>"
  "79f869a4490bb872a82b759fedfb8498")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MoveRobot)))
  "Returns md5sum for a message object of type 'MoveRobot"
  "79f869a4490bb872a82b759fedfb8498")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MoveRobot>)))
  "Returns full string definition for message of type '<MoveRobot>"
  (cl:format cl:nil "int32 position~%int32 bras~%int32 pince~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MoveRobot)))
  "Returns full string definition for message of type 'MoveRobot"
  (cl:format cl:nil "int32 position~%int32 bras~%int32 pince~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MoveRobot>))
  (cl:+ 0
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MoveRobot>))
  "Converts a ROS message object to a list"
  (cl:list 'MoveRobot
    (cl:cons ':position (position msg))
    (cl:cons ':bras (bras msg))
    (cl:cons ':pince (pince msg))
))
