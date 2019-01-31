; Auto-generated. Do not edit!


(cl:in-package automates-msg)


;//! \htmlinclude Sorties.msg.html

(cl:defclass <Sorties> (roslisp-msg-protocol:ros-message)
  ((sorties
    :reader sorties
    :initarg :sorties
    :type cl:integer
    :initform 0))
)

(cl:defclass Sorties (<Sorties>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Sorties>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Sorties)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name automates-msg:<Sorties> is deprecated: use automates-msg:Sorties instead.")))

(cl:ensure-generic-function 'sorties-val :lambda-list '(m))
(cl:defmethod sorties-val ((m <Sorties>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader automates-msg:sorties-val is deprecated.  Use automates-msg:sorties instead.")
  (sorties m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Sorties>) ostream)
  "Serializes a message object of type '<Sorties>"
  (cl:let* ((signed (cl:slot-value msg 'sorties)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Sorties>) istream)
  "Deserializes a message object of type '<Sorties>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'sorties) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Sorties>)))
  "Returns string type for a message object of type '<Sorties>"
  "automates/Sorties")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Sorties)))
  "Returns string type for a message object of type 'Sorties"
  "automates/Sorties")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Sorties>)))
  "Returns md5sum for a message object of type '<Sorties>"
  "eb8c2e3936f3777631d8548f59e5c804")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Sorties)))
  "Returns md5sum for a message object of type 'Sorties"
  "eb8c2e3936f3777631d8548f59e5c804")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Sorties>)))
  "Returns full string definition for message of type '<Sorties>"
  (cl:format cl:nil "int32 sorties~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Sorties)))
  "Returns full string definition for message of type 'Sorties"
  (cl:format cl:nil "int32 sorties~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Sorties>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Sorties>))
  "Converts a ROS message object to a list"
  (cl:list 'Sorties
    (cl:cons ':sorties (sorties msg))
))
