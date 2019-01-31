; Auto-generated. Do not edit!


(cl:in-package commande_locale-msg)


;//! \htmlinclude Msg_SensorState.msg.html

(cl:defclass <Msg_SensorState> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (CPI
    :reader CPI
    :initarg :CPI
    :type (cl:vector cl:boolean)
   :initform (cl:make-array 9 :element-type 'cl:boolean :initial-element cl:nil))
   (CP
    :reader CP
    :initarg :CP
    :type (cl:vector cl:boolean)
   :initform (cl:make-array 11 :element-type 'cl:boolean :initial-element cl:nil))
   (PS
    :reader PS
    :initarg :PS
    :type (cl:vector cl:boolean)
   :initform (cl:make-array 25 :element-type 'cl:boolean :initial-element cl:nil))
   (DG
    :reader DG
    :initarg :DG
    :type (cl:vector cl:boolean)
   :initform (cl:make-array 13 :element-type 'cl:boolean :initial-element cl:nil))
   (DD
    :reader DD
    :initarg :DD
    :type (cl:vector cl:boolean)
   :initform (cl:make-array 13 :element-type 'cl:boolean :initial-element cl:nil)))
)

(cl:defclass Msg_SensorState (<Msg_SensorState>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Msg_SensorState>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Msg_SensorState)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name commande_locale-msg:<Msg_SensorState> is deprecated: use commande_locale-msg:Msg_SensorState instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <Msg_SensorState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader commande_locale-msg:header-val is deprecated.  Use commande_locale-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'CPI-val :lambda-list '(m))
(cl:defmethod CPI-val ((m <Msg_SensorState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader commande_locale-msg:CPI-val is deprecated.  Use commande_locale-msg:CPI instead.")
  (CPI m))

(cl:ensure-generic-function 'CP-val :lambda-list '(m))
(cl:defmethod CP-val ((m <Msg_SensorState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader commande_locale-msg:CP-val is deprecated.  Use commande_locale-msg:CP instead.")
  (CP m))

(cl:ensure-generic-function 'PS-val :lambda-list '(m))
(cl:defmethod PS-val ((m <Msg_SensorState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader commande_locale-msg:PS-val is deprecated.  Use commande_locale-msg:PS instead.")
  (PS m))

(cl:ensure-generic-function 'DG-val :lambda-list '(m))
(cl:defmethod DG-val ((m <Msg_SensorState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader commande_locale-msg:DG-val is deprecated.  Use commande_locale-msg:DG instead.")
  (DG m))

(cl:ensure-generic-function 'DD-val :lambda-list '(m))
(cl:defmethod DD-val ((m <Msg_SensorState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader commande_locale-msg:DD-val is deprecated.  Use commande_locale-msg:DD instead.")
  (DD m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Msg_SensorState>) ostream)
  "Serializes a message object of type '<Msg_SensorState>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if ele 1 0)) ostream))
   (cl:slot-value msg 'CPI))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if ele 1 0)) ostream))
   (cl:slot-value msg 'CP))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if ele 1 0)) ostream))
   (cl:slot-value msg 'PS))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if ele 1 0)) ostream))
   (cl:slot-value msg 'DG))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if ele 1 0)) ostream))
   (cl:slot-value msg 'DD))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Msg_SensorState>) istream)
  "Deserializes a message object of type '<Msg_SensorState>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:setf (cl:slot-value msg 'CPI) (cl:make-array 9))
  (cl:let ((vals (cl:slot-value msg 'CPI)))
    (cl:dotimes (i 9)
    (cl:setf (cl:aref vals i) (cl:not (cl:zerop (cl:read-byte istream))))))
  (cl:setf (cl:slot-value msg 'CP) (cl:make-array 11))
  (cl:let ((vals (cl:slot-value msg 'CP)))
    (cl:dotimes (i 11)
    (cl:setf (cl:aref vals i) (cl:not (cl:zerop (cl:read-byte istream))))))
  (cl:setf (cl:slot-value msg 'PS) (cl:make-array 25))
  (cl:let ((vals (cl:slot-value msg 'PS)))
    (cl:dotimes (i 25)
    (cl:setf (cl:aref vals i) (cl:not (cl:zerop (cl:read-byte istream))))))
  (cl:setf (cl:slot-value msg 'DG) (cl:make-array 13))
  (cl:let ((vals (cl:slot-value msg 'DG)))
    (cl:dotimes (i 13)
    (cl:setf (cl:aref vals i) (cl:not (cl:zerop (cl:read-byte istream))))))
  (cl:setf (cl:slot-value msg 'DD) (cl:make-array 13))
  (cl:let ((vals (cl:slot-value msg 'DD)))
    (cl:dotimes (i 13)
    (cl:setf (cl:aref vals i) (cl:not (cl:zerop (cl:read-byte istream))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Msg_SensorState>)))
  "Returns string type for a message object of type '<Msg_SensorState>"
  "commande_locale/Msg_SensorState")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Msg_SensorState)))
  "Returns string type for a message object of type 'Msg_SensorState"
  "commande_locale/Msg_SensorState")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Msg_SensorState>)))
  "Returns md5sum for a message object of type '<Msg_SensorState>"
  "5e5483b92cc5dad298967591bceb2081")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Msg_SensorState)))
  "Returns md5sum for a message object of type 'Msg_SensorState"
  "5e5483b92cc5dad298967591bceb2081")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Msg_SensorState>)))
  "Returns full string definition for message of type '<Msg_SensorState>"
  (cl:format cl:nil "Header header~%~%bool[9] CPI~%bool[11] CP~%bool[25] PS~%bool[13] DG~%bool[13] DD~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Msg_SensorState)))
  "Returns full string definition for message of type 'Msg_SensorState"
  (cl:format cl:nil "Header header~%~%bool[9] CPI~%bool[11] CP~%bool[25] PS~%bool[13] DG~%bool[13] DD~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Msg_SensorState>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'CPI) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'CP) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'PS) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'DG) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'DD) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Msg_SensorState>))
  "Converts a ROS message object to a list"
  (cl:list 'Msg_SensorState
    (cl:cons ':header (header msg))
    (cl:cons ':CPI (CPI msg))
    (cl:cons ':CP (CP msg))
    (cl:cons ':PS (PS msg))
    (cl:cons ':DG (DG msg))
    (cl:cons ':DD (DD msg))
))
