; Auto-generated. Do not edit!


(cl:in-package automates-msg)


;//! \htmlinclude Entrees.msg.html

(cl:defclass <Entrees> (roslisp-msg-protocol:ros-message)
  ((entrees
    :reader entrees
    :initarg :entrees
    :type cl:integer
    :initform 0))
)

(cl:defclass Entrees (<Entrees>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Entrees>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Entrees)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name automates-msg:<Entrees> is deprecated: use automates-msg:Entrees instead.")))

(cl:ensure-generic-function 'entrees-val :lambda-list '(m))
(cl:defmethod entrees-val ((m <Entrees>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader automates-msg:entrees-val is deprecated.  Use automates-msg:entrees instead.")
  (entrees m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Entrees>) ostream)
  "Serializes a message object of type '<Entrees>"
  (cl:let* ((signed (cl:slot-value msg 'entrees)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Entrees>) istream)
  "Deserializes a message object of type '<Entrees>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'entrees) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Entrees>)))
  "Returns string type for a message object of type '<Entrees>"
  "automates/Entrees")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Entrees)))
  "Returns string type for a message object of type 'Entrees"
  "automates/Entrees")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Entrees>)))
  "Returns md5sum for a message object of type '<Entrees>"
  "2fd94acaf54653c950d522c68a591eb3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Entrees)))
  "Returns md5sum for a message object of type 'Entrees"
  "2fd94acaf54653c950d522c68a591eb3")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Entrees>)))
  "Returns full string definition for message of type '<Entrees>"
  (cl:format cl:nil "int32 entrees~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Entrees)))
  "Returns full string definition for message of type 'Entrees"
  (cl:format cl:nil "int32 entrees~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Entrees>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Entrees>))
  "Converts a ROS message object to a list"
  (cl:list 'Entrees
    (cl:cons ':entrees (entrees msg))
))
