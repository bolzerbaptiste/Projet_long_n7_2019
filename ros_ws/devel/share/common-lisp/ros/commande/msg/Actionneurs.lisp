; Auto-generated. Do not edit!


(cl:in-package commande-msg)


;//! \htmlinclude Actionneurs.msg.html

(cl:defclass <Actionneurs> (roslisp-msg-protocol:ros-message)
  ((actionneurs
    :reader actionneurs
    :initarg :actionneurs
    :type cl:integer
    :initform 0))
)

(cl:defclass Actionneurs (<Actionneurs>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Actionneurs>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Actionneurs)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name commande-msg:<Actionneurs> is deprecated: use commande-msg:Actionneurs instead.")))

(cl:ensure-generic-function 'actionneurs-val :lambda-list '(m))
(cl:defmethod actionneurs-val ((m <Actionneurs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader commande-msg:actionneurs-val is deprecated.  Use commande-msg:actionneurs instead.")
  (actionneurs m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Actionneurs>) ostream)
  "Serializes a message object of type '<Actionneurs>"
  (cl:let* ((signed (cl:slot-value msg 'actionneurs)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Actionneurs>) istream)
  "Deserializes a message object of type '<Actionneurs>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'actionneurs) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Actionneurs>)))
  "Returns string type for a message object of type '<Actionneurs>"
  "commande/Actionneurs")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Actionneurs)))
  "Returns string type for a message object of type 'Actionneurs"
  "commande/Actionneurs")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Actionneurs>)))
  "Returns md5sum for a message object of type '<Actionneurs>"
  "1a79d0b13aebfb5d0450ddf675b8fc68")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Actionneurs)))
  "Returns md5sum for a message object of type 'Actionneurs"
  "1a79d0b13aebfb5d0450ddf675b8fc68")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Actionneurs>)))
  "Returns full string definition for message of type '<Actionneurs>"
  (cl:format cl:nil "int64 actionneurs~%~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Actionneurs)))
  "Returns full string definition for message of type 'Actionneurs"
  (cl:format cl:nil "int64 actionneurs~%~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Actionneurs>))
  (cl:+ 0
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Actionneurs>))
  "Converts a ROS message object to a list"
  (cl:list 'Actionneurs
    (cl:cons ':actionneurs (actionneurs msg))
))
