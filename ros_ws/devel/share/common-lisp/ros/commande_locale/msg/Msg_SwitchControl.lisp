; Auto-generated. Do not edit!


(cl:in-package commande_locale-msg)


;//! \htmlinclude Msg_SwitchControl.msg.html

(cl:defclass <Msg_SwitchControl> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (LOCK
    :reader LOCK
    :initarg :LOCK
    :type (cl:vector cl:boolean)
   :initform (cl:make-array 13 :element-type 'cl:boolean :initial-element cl:nil))
   (RD
    :reader RD
    :initarg :RD
    :type (cl:vector cl:boolean)
   :initform (cl:make-array 13 :element-type 'cl:boolean :initial-element cl:nil))
   (RG
    :reader RG
    :initarg :RG
    :type (cl:vector cl:boolean)
   :initform (cl:make-array 13 :element-type 'cl:boolean :initial-element cl:nil)))
)

(cl:defclass Msg_SwitchControl (<Msg_SwitchControl>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Msg_SwitchControl>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Msg_SwitchControl)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name commande_locale-msg:<Msg_SwitchControl> is deprecated: use commande_locale-msg:Msg_SwitchControl instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <Msg_SwitchControl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader commande_locale-msg:header-val is deprecated.  Use commande_locale-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'LOCK-val :lambda-list '(m))
(cl:defmethod LOCK-val ((m <Msg_SwitchControl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader commande_locale-msg:LOCK-val is deprecated.  Use commande_locale-msg:LOCK instead.")
  (LOCK m))

(cl:ensure-generic-function 'RD-val :lambda-list '(m))
(cl:defmethod RD-val ((m <Msg_SwitchControl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader commande_locale-msg:RD-val is deprecated.  Use commande_locale-msg:RD instead.")
  (RD m))

(cl:ensure-generic-function 'RG-val :lambda-list '(m))
(cl:defmethod RG-val ((m <Msg_SwitchControl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader commande_locale-msg:RG-val is deprecated.  Use commande_locale-msg:RG instead.")
  (RG m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Msg_SwitchControl>) ostream)
  "Serializes a message object of type '<Msg_SwitchControl>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if ele 1 0)) ostream))
   (cl:slot-value msg 'LOCK))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if ele 1 0)) ostream))
   (cl:slot-value msg 'RD))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if ele 1 0)) ostream))
   (cl:slot-value msg 'RG))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Msg_SwitchControl>) istream)
  "Deserializes a message object of type '<Msg_SwitchControl>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:setf (cl:slot-value msg 'LOCK) (cl:make-array 13))
  (cl:let ((vals (cl:slot-value msg 'LOCK)))
    (cl:dotimes (i 13)
    (cl:setf (cl:aref vals i) (cl:not (cl:zerop (cl:read-byte istream))))))
  (cl:setf (cl:slot-value msg 'RD) (cl:make-array 13))
  (cl:let ((vals (cl:slot-value msg 'RD)))
    (cl:dotimes (i 13)
    (cl:setf (cl:aref vals i) (cl:not (cl:zerop (cl:read-byte istream))))))
  (cl:setf (cl:slot-value msg 'RG) (cl:make-array 13))
  (cl:let ((vals (cl:slot-value msg 'RG)))
    (cl:dotimes (i 13)
    (cl:setf (cl:aref vals i) (cl:not (cl:zerop (cl:read-byte istream))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Msg_SwitchControl>)))
  "Returns string type for a message object of type '<Msg_SwitchControl>"
  "commande_locale/Msg_SwitchControl")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Msg_SwitchControl)))
  "Returns string type for a message object of type 'Msg_SwitchControl"
  "commande_locale/Msg_SwitchControl")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Msg_SwitchControl>)))
  "Returns md5sum for a message object of type '<Msg_SwitchControl>"
  "0797883d1e8c7216af064c8c90c37c74")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Msg_SwitchControl)))
  "Returns md5sum for a message object of type 'Msg_SwitchControl"
  "0797883d1e8c7216af064c8c90c37c74")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Msg_SwitchControl>)))
  "Returns full string definition for message of type '<Msg_SwitchControl>"
  (cl:format cl:nil "Header header~%~%bool[13] LOCK~%bool[13] RD~%bool[13] RG~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Msg_SwitchControl)))
  "Returns full string definition for message of type 'Msg_SwitchControl"
  (cl:format cl:nil "Header header~%~%bool[13] LOCK~%bool[13] RD~%bool[13] RG~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Msg_SwitchControl>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'LOCK) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'RD) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'RG) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Msg_SwitchControl>))
  "Converts a ROS message object to a list"
  (cl:list 'Msg_SwitchControl
    (cl:cons ':header (header msg))
    (cl:cons ':LOCK (LOCK msg))
    (cl:cons ':RD (RD msg))
    (cl:cons ':RG (RG msg))
))
