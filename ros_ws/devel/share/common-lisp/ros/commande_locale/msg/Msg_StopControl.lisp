; Auto-generated. Do not edit!


(cl:in-package commande_locale-msg)


;//! \htmlinclude Msg_StopControl.msg.html

(cl:defclass <Msg_StopControl> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (STOP
    :reader STOP
    :initarg :STOP
    :type (cl:vector cl:boolean)
   :initform (cl:make-array 25 :element-type 'cl:boolean :initial-element cl:nil))
   (GO
    :reader GO
    :initarg :GO
    :type (cl:vector cl:boolean)
   :initform (cl:make-array 25 :element-type 'cl:boolean :initial-element cl:nil)))
)

(cl:defclass Msg_StopControl (<Msg_StopControl>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Msg_StopControl>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Msg_StopControl)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name commande_locale-msg:<Msg_StopControl> is deprecated: use commande_locale-msg:Msg_StopControl instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <Msg_StopControl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader commande_locale-msg:header-val is deprecated.  Use commande_locale-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'STOP-val :lambda-list '(m))
(cl:defmethod STOP-val ((m <Msg_StopControl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader commande_locale-msg:STOP-val is deprecated.  Use commande_locale-msg:STOP instead.")
  (STOP m))

(cl:ensure-generic-function 'GO-val :lambda-list '(m))
(cl:defmethod GO-val ((m <Msg_StopControl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader commande_locale-msg:GO-val is deprecated.  Use commande_locale-msg:GO instead.")
  (GO m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Msg_StopControl>) ostream)
  "Serializes a message object of type '<Msg_StopControl>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if ele 1 0)) ostream))
   (cl:slot-value msg 'STOP))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if ele 1 0)) ostream))
   (cl:slot-value msg 'GO))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Msg_StopControl>) istream)
  "Deserializes a message object of type '<Msg_StopControl>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:setf (cl:slot-value msg 'STOP) (cl:make-array 25))
  (cl:let ((vals (cl:slot-value msg 'STOP)))
    (cl:dotimes (i 25)
    (cl:setf (cl:aref vals i) (cl:not (cl:zerop (cl:read-byte istream))))))
  (cl:setf (cl:slot-value msg 'GO) (cl:make-array 25))
  (cl:let ((vals (cl:slot-value msg 'GO)))
    (cl:dotimes (i 25)
    (cl:setf (cl:aref vals i) (cl:not (cl:zerop (cl:read-byte istream))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Msg_StopControl>)))
  "Returns string type for a message object of type '<Msg_StopControl>"
  "commande_locale/Msg_StopControl")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Msg_StopControl)))
  "Returns string type for a message object of type 'Msg_StopControl"
  "commande_locale/Msg_StopControl")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Msg_StopControl>)))
  "Returns md5sum for a message object of type '<Msg_StopControl>"
  "3351a875ff673c8814a96d783877c306")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Msg_StopControl)))
  "Returns md5sum for a message object of type 'Msg_StopControl"
  "3351a875ff673c8814a96d783877c306")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Msg_StopControl>)))
  "Returns full string definition for message of type '<Msg_StopControl>"
  (cl:format cl:nil "Header header~%~%bool[25] STOP~%bool[25] GO~%~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Msg_StopControl)))
  "Returns full string definition for message of type 'Msg_StopControl"
  (cl:format cl:nil "Header header~%~%bool[25] STOP~%bool[25] GO~%~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Msg_StopControl>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'STOP) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'GO) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Msg_StopControl>))
  "Converts a ROS message object to a list"
  (cl:list 'Msg_StopControl
    (cl:cons ':header (header msg))
    (cl:cons ':STOP (STOP msg))
    (cl:cons ':GO (GO msg))
))
