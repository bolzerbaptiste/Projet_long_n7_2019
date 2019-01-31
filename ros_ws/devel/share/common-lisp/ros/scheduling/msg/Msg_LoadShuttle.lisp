; Auto-generated. Do not edit!


(cl:in-package scheduling-msg)


;//! \htmlinclude Msg_LoadShuttle.msg.html

(cl:defclass <Msg_LoadShuttle> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (shuttleType
    :reader shuttleType
    :initarg :shuttleType
    :type cl:fixnum
    :initform 0)
   (product
    :reader product
    :initarg :product
    :type cl:integer
    :initform 0)
   (firstDestination
    :reader firstDestination
    :initarg :firstDestination
    :type cl:integer
    :initform 0))
)

(cl:defclass Msg_LoadShuttle (<Msg_LoadShuttle>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Msg_LoadShuttle>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Msg_LoadShuttle)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name scheduling-msg:<Msg_LoadShuttle> is deprecated: use scheduling-msg:Msg_LoadShuttle instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <Msg_LoadShuttle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader scheduling-msg:header-val is deprecated.  Use scheduling-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'shuttleType-val :lambda-list '(m))
(cl:defmethod shuttleType-val ((m <Msg_LoadShuttle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader scheduling-msg:shuttleType-val is deprecated.  Use scheduling-msg:shuttleType instead.")
  (shuttleType m))

(cl:ensure-generic-function 'product-val :lambda-list '(m))
(cl:defmethod product-val ((m <Msg_LoadShuttle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader scheduling-msg:product-val is deprecated.  Use scheduling-msg:product instead.")
  (product m))

(cl:ensure-generic-function 'firstDestination-val :lambda-list '(m))
(cl:defmethod firstDestination-val ((m <Msg_LoadShuttle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader scheduling-msg:firstDestination-val is deprecated.  Use scheduling-msg:firstDestination instead.")
  (firstDestination m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Msg_LoadShuttle>) ostream)
  "Serializes a message object of type '<Msg_LoadShuttle>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'shuttleType)) ostream)
  (cl:let* ((signed (cl:slot-value msg 'product)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'firstDestination)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Msg_LoadShuttle>) istream)
  "Deserializes a message object of type '<Msg_LoadShuttle>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'shuttleType)) (cl:read-byte istream))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'product) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'firstDestination) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Msg_LoadShuttle>)))
  "Returns string type for a message object of type '<Msg_LoadShuttle>"
  "scheduling/Msg_LoadShuttle")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Msg_LoadShuttle)))
  "Returns string type for a message object of type 'Msg_LoadShuttle"
  "scheduling/Msg_LoadShuttle")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Msg_LoadShuttle>)))
  "Returns md5sum for a message object of type '<Msg_LoadShuttle>"
  "109f4b38f55347e749c6e9e0d96b9cd6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Msg_LoadShuttle)))
  "Returns md5sum for a message object of type 'Msg_LoadShuttle"
  "109f4b38f55347e749c6e9e0d96b9cd6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Msg_LoadShuttle>)))
  "Returns full string definition for message of type '<Msg_LoadShuttle>"
  (cl:format cl:nil "Header header~%uint8 shuttleType~%int32 product~%int32 firstDestination~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Msg_LoadShuttle)))
  "Returns full string definition for message of type 'Msg_LoadShuttle"
  (cl:format cl:nil "Header header~%uint8 shuttleType~%int32 product~%int32 firstDestination~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Msg_LoadShuttle>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     1
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Msg_LoadShuttle>))
  "Converts a ROS message object to a list"
  (cl:list 'Msg_LoadShuttle
    (cl:cons ':header (header msg))
    (cl:cons ':shuttleType (shuttleType msg))
    (cl:cons ':product (product msg))
    (cl:cons ':firstDestination (firstDestination msg))
))
