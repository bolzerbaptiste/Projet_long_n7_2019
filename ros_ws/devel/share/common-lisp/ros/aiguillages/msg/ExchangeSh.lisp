; Auto-generated. Do not edit!


(cl:in-package aiguillages-msg)


;//! \htmlinclude ExchangeSh.msg.html

(cl:defclass <ExchangeSh> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (handle
    :reader handle
    :initarg :handle
    :type cl:integer
    :initform 0))
)

(cl:defclass ExchangeSh (<ExchangeSh>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ExchangeSh>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ExchangeSh)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name aiguillages-msg:<ExchangeSh> is deprecated: use aiguillages-msg:ExchangeSh instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <ExchangeSh>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader aiguillages-msg:header-val is deprecated.  Use aiguillages-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'handle-val :lambda-list '(m))
(cl:defmethod handle-val ((m <ExchangeSh>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader aiguillages-msg:handle-val is deprecated.  Use aiguillages-msg:handle instead.")
  (handle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ExchangeSh>) ostream)
  "Serializes a message object of type '<ExchangeSh>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let* ((signed (cl:slot-value msg 'handle)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ExchangeSh>) istream)
  "Deserializes a message object of type '<ExchangeSh>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'handle) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ExchangeSh>)))
  "Returns string type for a message object of type '<ExchangeSh>"
  "aiguillages/ExchangeSh")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ExchangeSh)))
  "Returns string type for a message object of type 'ExchangeSh"
  "aiguillages/ExchangeSh")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ExchangeSh>)))
  "Returns md5sum for a message object of type '<ExchangeSh>"
  "1e674e2a2bd56787e34ea71041f1bf6d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ExchangeSh)))
  "Returns md5sum for a message object of type 'ExchangeSh"
  "1e674e2a2bd56787e34ea71041f1bf6d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ExchangeSh>)))
  "Returns full string definition for message of type '<ExchangeSh>"
  (cl:format cl:nil "Header header~%int32 handle~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ExchangeSh)))
  "Returns full string definition for message of type 'ExchangeSh"
  (cl:format cl:nil "Header header~%int32 handle~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ExchangeSh>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ExchangeSh>))
  "Converts a ROS message object to a list"
  (cl:list 'ExchangeSh
    (cl:cons ':header (header msg))
    (cl:cons ':handle (handle msg))
))
