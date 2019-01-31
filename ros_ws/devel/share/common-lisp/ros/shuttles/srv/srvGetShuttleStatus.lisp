; Auto-generated. Do not edit!


(cl:in-package shuttles-srv)


;//! \htmlinclude srvGetShuttleStatus-request.msg.html

(cl:defclass <srvGetShuttleStatus-request> (roslisp-msg-protocol:ros-message)
  ((handle
    :reader handle
    :initarg :handle
    :type cl:integer
    :initform 0))
)

(cl:defclass srvGetShuttleStatus-request (<srvGetShuttleStatus-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <srvGetShuttleStatus-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'srvGetShuttleStatus-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name shuttles-srv:<srvGetShuttleStatus-request> is deprecated: use shuttles-srv:srvGetShuttleStatus-request instead.")))

(cl:ensure-generic-function 'handle-val :lambda-list '(m))
(cl:defmethod handle-val ((m <srvGetShuttleStatus-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader shuttles-srv:handle-val is deprecated.  Use shuttles-srv:handle instead.")
  (handle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <srvGetShuttleStatus-request>) ostream)
  "Serializes a message object of type '<srvGetShuttleStatus-request>"
  (cl:let* ((signed (cl:slot-value msg 'handle)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <srvGetShuttleStatus-request>) istream)
  "Deserializes a message object of type '<srvGetShuttleStatus-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'handle) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<srvGetShuttleStatus-request>)))
  "Returns string type for a service object of type '<srvGetShuttleStatus-request>"
  "shuttles/srvGetShuttleStatusRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'srvGetShuttleStatus-request)))
  "Returns string type for a service object of type 'srvGetShuttleStatus-request"
  "shuttles/srvGetShuttleStatusRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<srvGetShuttleStatus-request>)))
  "Returns md5sum for a message object of type '<srvGetShuttleStatus-request>"
  "a4ce97941b4a653e0f9d7b798a04eeee")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'srvGetShuttleStatus-request)))
  "Returns md5sum for a message object of type 'srvGetShuttleStatus-request"
  "a4ce97941b4a653e0f9d7b798a04eeee")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<srvGetShuttleStatus-request>)))
  "Returns full string definition for message of type '<srvGetShuttleStatus-request>"
  (cl:format cl:nil "int32 handle~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'srvGetShuttleStatus-request)))
  "Returns full string definition for message of type 'srvGetShuttleStatus-request"
  (cl:format cl:nil "int32 handle~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <srvGetShuttleStatus-request>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <srvGetShuttleStatus-request>))
  "Converts a ROS message object to a list"
  (cl:list 'srvGetShuttleStatus-request
    (cl:cons ':handle (handle msg))
))
;//! \htmlinclude srvGetShuttleStatus-response.msg.html

(cl:defclass <srvGetShuttleStatus-response> (roslisp-msg-protocol:ros-message)
  ((destination
    :reader destination
    :initarg :destination
    :type cl:integer
    :initform 0)
   (handlePlatform
    :reader handlePlatform
    :initarg :handlePlatform
    :type cl:integer
    :initform 0)
   (product
    :reader product
    :initarg :product
    :type cl:integer
    :initform 0)
   (zone
    :reader zone
    :initarg :zone
    :type cl:integer
    :initform 0)
   (name
    :reader name
    :initarg :name
    :type cl:string
    :initform ""))
)

(cl:defclass srvGetShuttleStatus-response (<srvGetShuttleStatus-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <srvGetShuttleStatus-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'srvGetShuttleStatus-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name shuttles-srv:<srvGetShuttleStatus-response> is deprecated: use shuttles-srv:srvGetShuttleStatus-response instead.")))

(cl:ensure-generic-function 'destination-val :lambda-list '(m))
(cl:defmethod destination-val ((m <srvGetShuttleStatus-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader shuttles-srv:destination-val is deprecated.  Use shuttles-srv:destination instead.")
  (destination m))

(cl:ensure-generic-function 'handlePlatform-val :lambda-list '(m))
(cl:defmethod handlePlatform-val ((m <srvGetShuttleStatus-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader shuttles-srv:handlePlatform-val is deprecated.  Use shuttles-srv:handlePlatform instead.")
  (handlePlatform m))

(cl:ensure-generic-function 'product-val :lambda-list '(m))
(cl:defmethod product-val ((m <srvGetShuttleStatus-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader shuttles-srv:product-val is deprecated.  Use shuttles-srv:product instead.")
  (product m))

(cl:ensure-generic-function 'zone-val :lambda-list '(m))
(cl:defmethod zone-val ((m <srvGetShuttleStatus-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader shuttles-srv:zone-val is deprecated.  Use shuttles-srv:zone instead.")
  (zone m))

(cl:ensure-generic-function 'name-val :lambda-list '(m))
(cl:defmethod name-val ((m <srvGetShuttleStatus-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader shuttles-srv:name-val is deprecated.  Use shuttles-srv:name instead.")
  (name m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <srvGetShuttleStatus-response>) ostream)
  "Serializes a message object of type '<srvGetShuttleStatus-response>"
  (cl:let* ((signed (cl:slot-value msg 'destination)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
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
  (cl:let* ((signed (cl:slot-value msg 'product)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
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
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'name))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <srvGetShuttleStatus-response>) istream)
  "Deserializes a message object of type '<srvGetShuttleStatus-response>"
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
      (cl:setf (cl:slot-value msg 'handlePlatform) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
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
      (cl:setf (cl:slot-value msg 'zone) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<srvGetShuttleStatus-response>)))
  "Returns string type for a service object of type '<srvGetShuttleStatus-response>"
  "shuttles/srvGetShuttleStatusResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'srvGetShuttleStatus-response)))
  "Returns string type for a service object of type 'srvGetShuttleStatus-response"
  "shuttles/srvGetShuttleStatusResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<srvGetShuttleStatus-response>)))
  "Returns md5sum for a message object of type '<srvGetShuttleStatus-response>"
  "a4ce97941b4a653e0f9d7b798a04eeee")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'srvGetShuttleStatus-response)))
  "Returns md5sum for a message object of type 'srvGetShuttleStatus-response"
  "a4ce97941b4a653e0f9d7b798a04eeee")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<srvGetShuttleStatus-response>)))
  "Returns full string definition for message of type '<srvGetShuttleStatus-response>"
  (cl:format cl:nil "int32 destination~%int32 handlePlatform~%int32 product~%int32 zone~%string name~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'srvGetShuttleStatus-response)))
  "Returns full string definition for message of type 'srvGetShuttleStatus-response"
  (cl:format cl:nil "int32 destination~%int32 handlePlatform~%int32 product~%int32 zone~%string name~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <srvGetShuttleStatus-response>))
  (cl:+ 0
     4
     4
     4
     4
     4 (cl:length (cl:slot-value msg 'name))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <srvGetShuttleStatus-response>))
  "Converts a ROS message object to a list"
  (cl:list 'srvGetShuttleStatus-response
    (cl:cons ':destination (destination msg))
    (cl:cons ':handlePlatform (handlePlatform msg))
    (cl:cons ':product (product msg))
    (cl:cons ':zone (zone msg))
    (cl:cons ':name (name msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'srvGetShuttleStatus)))
  'srvGetShuttleStatus-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'srvGetShuttleStatus)))
  'srvGetShuttleStatus-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'srvGetShuttleStatus)))
  "Returns string type for a service object of type '<srvGetShuttleStatus>"
  "shuttles/srvGetShuttleStatus")