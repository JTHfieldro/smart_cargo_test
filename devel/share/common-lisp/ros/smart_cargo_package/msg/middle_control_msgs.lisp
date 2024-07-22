; Auto-generated. Do not edit!


(cl:in-package smart_cargo_package-msg)


;//! \htmlinclude middle_control_msgs.msg.html

(cl:defclass <middle_control_msgs> (roslisp-msg-protocol:ros-message)
  ((time_stamp
    :reader time_stamp
    :initarg :time_stamp
    :type cl:real
    :initform 0)
   (target_object
    :reader target_object
    :initarg :target_object
    :type cl:integer
    :initform 0)
   (action
    :reader action
    :initarg :action
    :type cl:integer
    :initform 0))
)

(cl:defclass middle_control_msgs (<middle_control_msgs>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <middle_control_msgs>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'middle_control_msgs)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name smart_cargo_package-msg:<middle_control_msgs> is deprecated: use smart_cargo_package-msg:middle_control_msgs instead.")))

(cl:ensure-generic-function 'time_stamp-val :lambda-list '(m))
(cl:defmethod time_stamp-val ((m <middle_control_msgs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smart_cargo_package-msg:time_stamp-val is deprecated.  Use smart_cargo_package-msg:time_stamp instead.")
  (time_stamp m))

(cl:ensure-generic-function 'target_object-val :lambda-list '(m))
(cl:defmethod target_object-val ((m <middle_control_msgs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smart_cargo_package-msg:target_object-val is deprecated.  Use smart_cargo_package-msg:target_object instead.")
  (target_object m))

(cl:ensure-generic-function 'action-val :lambda-list '(m))
(cl:defmethod action-val ((m <middle_control_msgs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smart_cargo_package-msg:action-val is deprecated.  Use smart_cargo_package-msg:action instead.")
  (action m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <middle_control_msgs>) ostream)
  "Serializes a message object of type '<middle_control_msgs>"
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
  (cl:let* ((signed (cl:slot-value msg 'target_object)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'action)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <middle_control_msgs>) istream)
  "Deserializes a message object of type '<middle_control_msgs>"
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
      (cl:setf (cl:slot-value msg 'target_object) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'action) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<middle_control_msgs>)))
  "Returns string type for a message object of type '<middle_control_msgs>"
  "smart_cargo_package/middle_control_msgs")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'middle_control_msgs)))
  "Returns string type for a message object of type 'middle_control_msgs"
  "smart_cargo_package/middle_control_msgs")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<middle_control_msgs>)))
  "Returns md5sum for a message object of type '<middle_control_msgs>"
  "8d58a37429769e2a5c482d5c6ba001eb")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'middle_control_msgs)))
  "Returns md5sum for a message object of type 'middle_control_msgs"
  "8d58a37429769e2a5c482d5c6ba001eb")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<middle_control_msgs>)))
  "Returns full string definition for message of type '<middle_control_msgs>"
  (cl:format cl:nil "time time_stamp      # Message 발행 시간 (ros::Time)~%int32 target_object  # 대상 객체 H/W Index Enum~%int32 action         # 명령 동작 Action Index Enum (홀수만 와야 한다)~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'middle_control_msgs)))
  "Returns full string definition for message of type 'middle_control_msgs"
  (cl:format cl:nil "time time_stamp      # Message 발행 시간 (ros::Time)~%int32 target_object  # 대상 객체 H/W Index Enum~%int32 action         # 명령 동작 Action Index Enum (홀수만 와야 한다)~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <middle_control_msgs>))
  (cl:+ 0
     8
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <middle_control_msgs>))
  "Converts a ROS message object to a list"
  (cl:list 'middle_control_msgs
    (cl:cons ':time_stamp (time_stamp msg))
    (cl:cons ':target_object (target_object msg))
    (cl:cons ':action (action msg))
))
