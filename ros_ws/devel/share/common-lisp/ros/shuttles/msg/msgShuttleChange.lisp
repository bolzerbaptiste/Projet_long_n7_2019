; Auto-generated. Do not edit!


(cl:in-package shuttles-msg)


;//! \htmlinclude msgShuttleChange.msg.html

(cl:defclass <msgShuttleChange> (roslisp-msg-protocol:ros-message)
  ((handle
    :reader handle
    :initarg :handle
    :type cl:integer
    :initform 0)
   (argument
    :reader argument
    :initarg :argument
    :type cl:integer
    :initform 0))
)

(cl:defclass msgShuttleChange (<msgShuttleChange>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <msgShuttleChange>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'msgShuttleChange)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name shuttles-msg:<msgShuttleChange> is deprecated: use shuttles-msg:msgShuttleChange instead.")))

(cl:ensure-generic-function 'handle-val :lambda-list '(m))
(cl:defmethod handle-val ((m <msgShuttleChange>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader shuttles-msg:handle-val is deprecated.  Use shuttles-msg:handle instead.")
  (handle m))

(cl:ensure-generic-function 'argument-val :lambda-list '(m))
(cl:defmethod argument-val ((m <msgShuttleChange>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader shuttles-msg:argument-val is deprecated.  Use shuttles-msg:argument instead.")
  (argument m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <msgShuttleChange>) ostream)
  "Serializes a message object of type '<msgShuttleChange>"
  (cl:let* ((signed (cl:slot-value msg 'handle)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'argument)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <msgShuttleChange>) istream)
  "Deserializes a message object of type '<msgShuttleChange>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'handle) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'argument) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<msgShuttleChange>)))
  "Returns string type for a message object of type '<msgShuttleChange>"
  "shuttles/msgShuttleChange")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'msgShuttleChange)))
  "Returns string type for a message object of type 'msgShuttleChange"
  "shuttles/msgShuttleChange")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<msgShuttleChange>)))
  "Returns md5sum for a message object of type '<msgShuttleChange>"
  "02c8ec5acb6ca55401e7f0fabb5b8e17")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'msgShuttleChange)))
  "Returns md5sum for a message object of type 'msgShuttleChange"
  "02c8ec5acb6ca55401e7f0fabb5b8e17")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<msgShuttleChange>)))
  "Returns full string definition for message of type '<msgShuttleChange>"
  (cl:format cl:nil "# argument = destination or product~%~%int32 handle~%int32 argument ~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'msgShuttleChange)))
  "Returns full string definition for message of type 'msgShuttleChange"
  (cl:format cl:nil "# argument = destination or product~%~%int32 handle~%int32 argument ~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <msgShuttleChange>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <msgShuttleChange>))
  "Converts a ROS message object to a list"
  (cl:list 'msgShuttleChange
    (cl:cons ':handle (handle msg))
    (cl:cons ':argument (argument msg))
))
