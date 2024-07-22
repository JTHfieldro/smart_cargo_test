; Auto-generated. Do not edit!


(cl:in-package smart_cargo_package-msg)


;//! \htmlinclude sensor_signal_msgs.msg.html

(cl:defclass <sensor_signal_msgs> (roslisp-msg-protocol:ros-message)
  ((time_stamp
    :reader time_stamp
    :initarg :time_stamp
    :type cl:real
    :initform 0)
   (index
    :reader index
    :initarg :index
    :type cl:integer
    :initform 0)
   (value
    :reader value
    :initarg :value
    :type cl:integer
    :initform 0))
)

(cl:defclass sensor_signal_msgs (<sensor_signal_msgs>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <sensor_signal_msgs>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'sensor_signal_msgs)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name smart_cargo_package-msg:<sensor_signal_msgs> is deprecated: use smart_cargo_package-msg:sensor_signal_msgs instead.")))

(cl:ensure-generic-function 'time_stamp-val :lambda-list '(m))
(cl:defmethod time_stamp-val ((m <sensor_signal_msgs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smart_cargo_package-msg:time_stamp-val is deprecated.  Use smart_cargo_package-msg:time_stamp instead.")
  (time_stamp m))

(cl:ensure-generic-function 'index-val :lambda-list '(m))
(cl:defmethod index-val ((m <sensor_signal_msgs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smart_cargo_package-msg:index-val is deprecated.  Use smart_cargo_package-msg:index instead.")
  (index m))

(cl:ensure-generic-function 'value-val :lambda-list '(m))
(cl:defmethod value-val ((m <sensor_signal_msgs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smart_cargo_package-msg:value-val is deprecated.  Use smart_cargo_package-msg:value instead.")
  (value m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <sensor_signal_msgs>) ostream)
  "Serializes a message object of type '<sensor_signal_msgs>"
  (cl:let ((__sec (cl:floor (cl:slot-value msg 'time_stamp)))
        (__nsec (cl:round (cl:* 1e9 (cl:- (cl:slot-value msg 'time_stamp) (cl:floor (cl:slot-value msg 'time_stamp)))))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 0) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __nsec) ostream))
  (cl:let* ((signed (cl:slot-value msg 'index)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'value)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <sensor_signal_msgs>) istream)
  "Deserializes a message object of type '<sensor_signal_msgs>"
    (cl:let ((__sec 0) (__nsec 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 0) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __nsec) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'time_stamp) (cl:+ (cl:coerce __sec 'cl:double-float) (cl:/ __nsec 1e9))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'index) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'value) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<sensor_signal_msgs>)))
  "Returns string type for a message object of type '<sensor_signal_msgs>"
  "smart_cargo_package/sensor_signal_msgs")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'sensor_signal_msgs)))
  "Returns string type for a message object of type 'sensor_signal_msgs"
  "smart_cargo_package/sensor_signal_msgs")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<sensor_signal_msgs>)))
  "Returns md5sum for a message object of type '<sensor_signal_msgs>"
  "1c7a1b51f4e21ef105c7e6881304d350")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'sensor_signal_msgs)))
  "Returns md5sum for a message object of type 'sensor_signal_msgs"
  "1c7a1b51f4e21ef105c7e6881304d350")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<sensor_signal_msgs>)))
  "Returns full string definition for message of type '<sensor_signal_msgs>"
  (cl:format cl:nil "time time_stamp  # Message 발행 시간 (ros::Time)~%int32 index       # DI/DO Signal Index Enum~%int32 value      # Signal Value~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'sensor_signal_msgs)))
  "Returns full string definition for message of type 'sensor_signal_msgs"
  (cl:format cl:nil "time time_stamp  # Message 발행 시간 (ros::Time)~%int32 index       # DI/DO Signal Index Enum~%int32 value      # Signal Value~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <sensor_signal_msgs>))
  (cl:+ 0
     8
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <sensor_signal_msgs>))
  "Converts a ROS message object to a list"
  (cl:list 'sensor_signal_msgs
    (cl:cons ':time_stamp (time_stamp msg))
    (cl:cons ':index (index msg))
    (cl:cons ':value (value msg))
))
