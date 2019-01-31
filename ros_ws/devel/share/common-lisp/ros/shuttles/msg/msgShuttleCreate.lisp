; Auto-generated. Do not edit!


(cl:in-package shuttles-msg)


;//! \htmlinclude msgShuttleCreate.msg.html

(cl:defclass <msgShuttleCreate> (roslisp-msg-protocol:ros-message)
  ((name
    :reader name
    :initarg :name
    :type cl:string
    :initform "")
   (destination
    :reader destination
    :initarg :destination
    :type cl:integer
    :initform 0)
   (product
    :reader product
    :initarg :product
    :type cl:integer
    :initform 0)
   (handle
    :reader handle
    :initarg :handle
    :type cl:integer
    :initform 0)
   (handlePlatform
    :reader handlePlatform
    :initarg :handlePlatform
    :type cl:integer
    :initform 0)
   (zone
    :reader zone
    :initarg :zone
    :type cl:integer
    :initform 0))
)

(cl:defclass msgShuttleCreate (<msgShuttleCreate>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <msgShuttleCreate>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'msgShuttleCreate)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name shuttles-msg:<msgShuttleCreate> is deprecated: use shuttles-msg:msgShuttleCreate instead.")))

(cl:ensure-generic-function 'name-val :lambda-list '(m))
(cl:defmethod name-val ((m <msgShuttleCreate>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader shuttles-msg:name-val is deprecated.  Use shuttles-msg:name instead.")
  (name m))

(cl:ensure-generic-function 'destination-val :lambda-list '(m))
(cl:defmethod destination-val ((m <msgShuttleCreate>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader shuttles-msg:destination-val is deprecated.  Use shuttles-msg:destination instead.")
  (destination m))

(cl:ensure-generic-function 'product-val :lambda-list '(m))
(cl:defmethod product-val ((m <msgShuttleCreate>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader shuttles-msg:product-val is deprecated.  Use shuttles-msg:product instead.")
  (product m))

(cl:ensure-generic-function 'handle-val :lambda-list '(m))
(cl:defmethod handle-val ((m <msgShuttleCreate>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader shuttles-msg:handle-val is deprecated.  Use shuttles-msg:handle instead.")
  (handle m))

(cl:ensure-generic-function 'handlePlatform-val :lambda-list '(m))
(cl:defmethod handlePlatform-val ((m <msgShuttleCreate>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader shuttles-msg:handlePlatform-val is deprecated.  Use shuttles-msg:handlePlatform instead.")
  (handlePlatform m))

(cl:ensure-generic-function 'zone-val :lambda-list '(m))
(cl:defmethod zone-val ((m <msgShuttleCreate>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader shuttles-msg:zone-val is deprecated.  Use shuttles-msg:zone instead.")
  (zone m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <msgShuttleCreate>) ostream)
  "Serializes a message object of type '<msgShuttleCreate>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'name))
  (cl:let* ((signed (cl:slot-value msg 'destination)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'product)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'handle)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'handlePlatform)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'zone)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <msgShuttleCreate>) istream)
  "Deserializes a message object of type '<msgShuttleCreate>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'destination) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
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
      (cl:setf (cl:slot-value msg 'handle) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'handlePlatform) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'zone) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<msgShuttleCreate>)))
  "Returns string type for a message object of type '<msgShuttleCreate>"
  "shuttles/msgShuttleCreate")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'msgShuttleCreate)))
  "Returns string type for a message object of type 'msgShuttleCreate"
  "shuttles/msgShuttleCreate")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<msgShuttleCreate>)))
  "Returns md5sum for a message object of type '<msgShuttleCreate>"
  "bbe2beba2a1f997c0e8c09a3d7eb1f7a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'msgShuttleCreate)))
  "Returns md5sum for a message object of type 'msgShuttleCreate"
  "bbe2beba2a1f997c0e8c09a3d7eb1f7a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<msgShuttleCreate>)))
  "Returns full string definition for message of type '<msgShuttleCreate>"
  (cl:format cl:nil "string name~%int32 destination~%int32 product~%int32 handle~%int32 handlePlatform~%int32 zone~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'msgShuttleCreate)))
  "Returns full string definition for message of type 'msgShuttleCreate"
  (cl:format cl:nil "string name~%int32 destination~%int32 product~%int32 handle~%int32 handlePlatform~%int32 zone~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <msgShuttleCreate>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'name))
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <msgShuttleCreate>))
  "Converts a ROS message object to a list"
  (cl:list 'msgShuttleCreate
    (cl:cons ':name (name msg))
    (cl:cons ':destination (destination msg))
    (cl:cons ':product (product msg))
    (cl:cons ':handle (handle msg))
    (cl:cons ':handlePlatform (handlePlatform msg))
    (cl:cons ':zone (zone msg))
))
