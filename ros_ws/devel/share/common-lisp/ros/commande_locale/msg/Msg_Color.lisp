; Auto-generated. Do not edit!


(cl:in-package commande_locale-msg)


;//! \htmlinclude Msg_Color.msg.html

(cl:defclass <Msg_Color> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (Handle
    :reader Handle
    :initarg :Handle
    :type cl:integer
    :initform 0)
   (Color
    :reader Color
    :initarg :Color
    :type cl:integer
    :initform 0))
)

(cl:defclass Msg_Color (<Msg_Color>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Msg_Color>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Msg_Color)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name commande_locale-msg:<Msg_Color> is deprecated: use commande_locale-msg:Msg_Color instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <Msg_Color>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader commande_locale-msg:header-val is deprecated.  Use commande_locale-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'Handle-val :lambda-list '(m))
(cl:defmethod Handle-val ((m <Msg_Color>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader commande_locale-msg:Handle-val is deprecated.  Use commande_locale-msg:Handle instead.")
  (Handle m))

(cl:ensure-generic-function 'Color-val :lambda-list '(m))
(cl:defmethod Color-val ((m <Msg_Color>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader commande_locale-msg:Color-val is deprecated.  Use commande_locale-msg:Color instead.")
  (Color m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Msg_Color>) ostream)
  "Serializes a message object of type '<Msg_Color>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let* ((signed (cl:slot-value msg 'Handle)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'Color)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Msg_Color>) istream)
  "Deserializes a message object of type '<Msg_Color>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'Handle) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'Color) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Msg_Color>)))
  "Returns string type for a message object of type '<Msg_Color>"
  "commande_locale/Msg_Color")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Msg_Color)))
  "Returns string type for a message object of type 'Msg_Color"
  "commande_locale/Msg_Color")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Msg_Color>)))
  "Returns md5sum for a message object of type '<Msg_Color>"
  "bc181530e810a3c987e52bb86805fe8b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Msg_Color)))
  "Returns md5sum for a message object of type 'Msg_Color"
  "bc181530e810a3c987e52bb86805fe8b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Msg_Color>)))
  "Returns full string definition for message of type '<Msg_Color>"
  (cl:format cl:nil "Header header~%~%int32 Handle~%int32 Color~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Msg_Color)))
  "Returns full string definition for message of type 'Msg_Color"
  (cl:format cl:nil "Header header~%~%int32 Handle~%int32 Color~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Msg_Color>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Msg_Color>))
  "Converts a ROS message object to a list"
  (cl:list 'Msg_Color
    (cl:cons ':header (header msg))
    (cl:cons ':Handle (Handle msg))
    (cl:cons ':Color (Color msg))
))
