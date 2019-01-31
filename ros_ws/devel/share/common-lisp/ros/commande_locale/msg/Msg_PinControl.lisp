; Auto-generated. Do not edit!


(cl:in-package commande_locale-msg)


;//! \htmlinclude Msg_PinControl.msg.html

(cl:defclass <Msg_PinControl> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (PINON
    :reader PINON
    :initarg :PINON
    :type (cl:vector cl:boolean)
   :initform (cl:make-array 9 :element-type 'cl:boolean :initial-element cl:nil))
   (PINOFF
    :reader PINOFF
    :initarg :PINOFF
    :type (cl:vector cl:boolean)
   :initform (cl:make-array 9 :element-type 'cl:boolean :initial-element cl:nil)))
)

(cl:defclass Msg_PinControl (<Msg_PinControl>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Msg_PinControl>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Msg_PinControl)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name commande_locale-msg:<Msg_PinControl> is deprecated: use commande_locale-msg:Msg_PinControl instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <Msg_PinControl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader commande_locale-msg:header-val is deprecated.  Use commande_locale-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'PINON-val :lambda-list '(m))
(cl:defmethod PINON-val ((m <Msg_PinControl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader commande_locale-msg:PINON-val is deprecated.  Use commande_locale-msg:PINON instead.")
  (PINON m))

(cl:ensure-generic-function 'PINOFF-val :lambda-list '(m))
(cl:defmethod PINOFF-val ((m <Msg_PinControl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader commande_locale-msg:PINOFF-val is deprecated.  Use commande_locale-msg:PINOFF instead.")
  (PINOFF m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Msg_PinControl>) ostream)
  "Serializes a message object of type '<Msg_PinControl>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if ele 1 0)) ostream))
   (cl:slot-value msg 'PINON))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if ele 1 0)) ostream))
   (cl:slot-value msg 'PINOFF))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Msg_PinControl>) istream)
  "Deserializes a message object of type '<Msg_PinControl>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:setf (cl:slot-value msg 'PINON) (cl:make-array 9))
  (cl:let ((vals (cl:slot-value msg 'PINON)))
    (cl:dotimes (i 9)
    (cl:setf (cl:aref vals i) (cl:not (cl:zerop (cl:read-byte istream))))))
  (cl:setf (cl:slot-value msg 'PINOFF) (cl:make-array 9))
  (cl:let ((vals (cl:slot-value msg 'PINOFF)))
    (cl:dotimes (i 9)
    (cl:setf (cl:aref vals i) (cl:not (cl:zerop (cl:read-byte istream))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Msg_PinControl>)))
  "Returns string type for a message object of type '<Msg_PinControl>"
  "commande_locale/Msg_PinControl")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Msg_PinControl)))
  "Returns string type for a message object of type 'Msg_PinControl"
  "commande_locale/Msg_PinControl")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Msg_PinControl>)))
  "Returns md5sum for a message object of type '<Msg_PinControl>"
  "bdef2ee2c42b42b5f1efd9be2b5cd147")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Msg_PinControl)))
  "Returns md5sum for a message object of type 'Msg_PinControl"
  "bdef2ee2c42b42b5f1efd9be2b5cd147")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Msg_PinControl>)))
  "Returns full string definition for message of type '<Msg_PinControl>"
  (cl:format cl:nil "Header header~%~%bool[9] PINON   ~%bool[9] PINOFF~%~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Msg_PinControl)))
  "Returns full string definition for message of type 'Msg_PinControl"
  (cl:format cl:nil "Header header~%~%bool[9] PINON   ~%bool[9] PINOFF~%~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Msg_PinControl>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'PINON) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'PINOFF) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Msg_PinControl>))
  "Converts a ROS message object to a list"
  (cl:list 'Msg_PinControl
    (cl:cons ':header (header msg))
    (cl:cons ':PINON (PINON msg))
    (cl:cons ':PINOFF (PINOFF msg))
))
