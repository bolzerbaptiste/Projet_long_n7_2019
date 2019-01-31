; Auto-generated. Do not edit!


(cl:in-package commande-msg)


;//! \htmlinclude Capteurs.msg.html

(cl:defclass <Capteurs> (roslisp-msg-protocol:ros-message)
  ((capteurs
    :reader capteurs
    :initarg :capteurs
    :type cl:integer
    :initform 0))
)

(cl:defclass Capteurs (<Capteurs>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Capteurs>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Capteurs)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name commande-msg:<Capteurs> is deprecated: use commande-msg:Capteurs instead.")))

(cl:ensure-generic-function 'capteurs-val :lambda-list '(m))
(cl:defmethod capteurs-val ((m <Capteurs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader commande-msg:capteurs-val is deprecated.  Use commande-msg:capteurs instead.")
  (capteurs m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Capteurs>) ostream)
  "Serializes a message object of type '<Capteurs>"
  (cl:let* ((signed (cl:slot-value msg 'capteurs)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Capteurs>) istream)
  "Deserializes a message object of type '<Capteurs>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'capteurs) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Capteurs>)))
  "Returns string type for a message object of type '<Capteurs>"
  "commande/Capteurs")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Capteurs)))
  "Returns string type for a message object of type 'Capteurs"
  "commande/Capteurs")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Capteurs>)))
  "Returns md5sum for a message object of type '<Capteurs>"
  "bf794154bbba9db270fca7e0cc669d41")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Capteurs)))
  "Returns md5sum for a message object of type 'Capteurs"
  "bf794154bbba9db270fca7e0cc669d41")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Capteurs>)))
  "Returns full string definition for message of type '<Capteurs>"
  (cl:format cl:nil "int64 capteurs~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Capteurs)))
  "Returns full string definition for message of type 'Capteurs"
  (cl:format cl:nil "int64 capteurs~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Capteurs>))
  (cl:+ 0
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Capteurs>))
  "Converts a ROS message object to a list"
  (cl:list 'Capteurs
    (cl:cons ':capteurs (capteurs msg))
))
