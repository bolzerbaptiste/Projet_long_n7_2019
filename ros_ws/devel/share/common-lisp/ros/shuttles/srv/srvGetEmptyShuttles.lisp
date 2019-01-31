; Auto-generated. Do not edit!


(cl:in-package shuttles-srv)


;//! \htmlinclude srvGetEmptyShuttles-request.msg.html

(cl:defclass <srvGetEmptyShuttles-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass srvGetEmptyShuttles-request (<srvGetEmptyShuttles-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <srvGetEmptyShuttles-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'srvGetEmptyShuttles-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name shuttles-srv:<srvGetEmptyShuttles-request> is deprecated: use shuttles-srv:srvGetEmptyShuttles-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <srvGetEmptyShuttles-request>) ostream)
  "Serializes a message object of type '<srvGetEmptyShuttles-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <srvGetEmptyShuttles-request>) istream)
  "Deserializes a message object of type '<srvGetEmptyShuttles-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<srvGetEmptyShuttles-request>)))
  "Returns string type for a service object of type '<srvGetEmptyShuttles-request>"
  "shuttles/srvGetEmptyShuttlesRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'srvGetEmptyShuttles-request)))
  "Returns string type for a service object of type 'srvGetEmptyShuttles-request"
  "shuttles/srvGetEmptyShuttlesRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<srvGetEmptyShuttles-request>)))
  "Returns md5sum for a message object of type '<srvGetEmptyShuttles-request>"
  "af5d249f87e707b5fe578809b83b41ae")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'srvGetEmptyShuttles-request)))
  "Returns md5sum for a message object of type 'srvGetEmptyShuttles-request"
  "af5d249f87e707b5fe578809b83b41ae")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<srvGetEmptyShuttles-request>)))
  "Returns full string definition for message of type '<srvGetEmptyShuttles-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'srvGetEmptyShuttles-request)))
  "Returns full string definition for message of type 'srvGetEmptyShuttles-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <srvGetEmptyShuttles-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <srvGetEmptyShuttles-request>))
  "Converts a ROS message object to a list"
  (cl:list 'srvGetEmptyShuttles-request
))
;//! \htmlinclude srvGetEmptyShuttles-response.msg.html

(cl:defclass <srvGetEmptyShuttles-response> (roslisp-msg-protocol:ros-message)
  ((handles
    :reader handles
    :initarg :handles
    :type (cl:vector cl:integer)
   :initform (cl:make-array 0 :element-type 'cl:integer :initial-element 0))
   (zones
    :reader zones
    :initarg :zones
    :type (cl:vector cl:integer)
   :initform (cl:make-array 0 :element-type 'cl:integer :initial-element 0)))
)

(cl:defclass srvGetEmptyShuttles-response (<srvGetEmptyShuttles-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <srvGetEmptyShuttles-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'srvGetEmptyShuttles-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name shuttles-srv:<srvGetEmptyShuttles-response> is deprecated: use shuttles-srv:srvGetEmptyShuttles-response instead.")))

(cl:ensure-generic-function 'handles-val :lambda-list '(m))
(cl:defmethod handles-val ((m <srvGetEmptyShuttles-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader shuttles-srv:handles-val is deprecated.  Use shuttles-srv:handles instead.")
  (handles m))

(cl:ensure-generic-function 'zones-val :lambda-list '(m))
(cl:defmethod zones-val ((m <srvGetEmptyShuttles-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader shuttles-srv:zones-val is deprecated.  Use shuttles-srv:zones instead.")
  (zones m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <srvGetEmptyShuttles-response>) ostream)
  "Serializes a message object of type '<srvGetEmptyShuttles-response>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'handles))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    ))
   (cl:slot-value msg 'handles))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'zones))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    ))
   (cl:slot-value msg 'zones))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <srvGetEmptyShuttles-response>) istream)
  "Deserializes a message object of type '<srvGetEmptyShuttles-response>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'handles) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'handles)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296)))))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'zones) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'zones)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296)))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<srvGetEmptyShuttles-response>)))
  "Returns string type for a service object of type '<srvGetEmptyShuttles-response>"
  "shuttles/srvGetEmptyShuttlesResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'srvGetEmptyShuttles-response)))
  "Returns string type for a service object of type 'srvGetEmptyShuttles-response"
  "shuttles/srvGetEmptyShuttlesResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<srvGetEmptyShuttles-response>)))
  "Returns md5sum for a message object of type '<srvGetEmptyShuttles-response>"
  "af5d249f87e707b5fe578809b83b41ae")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'srvGetEmptyShuttles-response)))
  "Returns md5sum for a message object of type 'srvGetEmptyShuttles-response"
  "af5d249f87e707b5fe578809b83b41ae")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<srvGetEmptyShuttles-response>)))
  "Returns full string definition for message of type '<srvGetEmptyShuttles-response>"
  (cl:format cl:nil "int32[] handles~%int32[] zones~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'srvGetEmptyShuttles-response)))
  "Returns full string definition for message of type 'srvGetEmptyShuttles-response"
  (cl:format cl:nil "int32[] handles~%int32[] zones~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <srvGetEmptyShuttles-response>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'handles) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'zones) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <srvGetEmptyShuttles-response>))
  "Converts a ROS message object to a list"
  (cl:list 'srvGetEmptyShuttles-response
    (cl:cons ':handles (handles msg))
    (cl:cons ':zones (zones msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'srvGetEmptyShuttles)))
  'srvGetEmptyShuttles-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'srvGetEmptyShuttles)))
  'srvGetEmptyShuttles-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'srvGetEmptyShuttles)))
  "Returns string type for a service object of type '<srvGetEmptyShuttles>"
  "shuttles/srvGetEmptyShuttles")