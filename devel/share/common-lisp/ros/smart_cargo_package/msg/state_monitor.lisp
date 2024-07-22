; Auto-generated. Do not edit!


(cl:in-package smart_cargo_package-msg)


;//! \htmlinclude state_monitor.msg.html

(cl:defclass <state_monitor> (roslisp-msg-protocol:ros-message)
  ((system_state
    :reader system_state
    :initarg :system_state
    :type cl:string
    :initform "")
   (door_state
    :reader door_state
    :initarg :door_state
    :type cl:string
    :initform "")
   (handler_state
    :reader handler_state
    :initarg :handler_state
    :type cl:string
    :initform "")
   (docking_state
    :reader docking_state
    :initarg :docking_state
    :type cl:string
    :initform "")
   (type
    :reader type
    :initarg :type
    :type cl:string
    :initform ""))
)

(cl:defclass state_monitor (<state_monitor>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <state_monitor>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'state_monitor)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name smart_cargo_package-msg:<state_monitor> is deprecated: use smart_cargo_package-msg:state_monitor instead.")))

(cl:ensure-generic-function 'system_state-val :lambda-list '(m))
(cl:defmethod system_state-val ((m <state_monitor>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smart_cargo_package-msg:system_state-val is deprecated.  Use smart_cargo_package-msg:system_state instead.")
  (system_state m))

(cl:ensure-generic-function 'door_state-val :lambda-list '(m))
(cl:defmethod door_state-val ((m <state_monitor>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smart_cargo_package-msg:door_state-val is deprecated.  Use smart_cargo_package-msg:door_state instead.")
  (door_state m))

(cl:ensure-generic-function 'handler_state-val :lambda-list '(m))
(cl:defmethod handler_state-val ((m <state_monitor>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smart_cargo_package-msg:handler_state-val is deprecated.  Use smart_cargo_package-msg:handler_state instead.")
  (handler_state m))

(cl:ensure-generic-function 'docking_state-val :lambda-list '(m))
(cl:defmethod docking_state-val ((m <state_monitor>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smart_cargo_package-msg:docking_state-val is deprecated.  Use smart_cargo_package-msg:docking_state instead.")
  (docking_state m))

(cl:ensure-generic-function 'type-val :lambda-list '(m))
(cl:defmethod type-val ((m <state_monitor>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smart_cargo_package-msg:type-val is deprecated.  Use smart_cargo_package-msg:type instead.")
  (type m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <state_monitor>) ostream)
  "Serializes a message object of type '<state_monitor>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'system_state))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'system_state))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'door_state))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'door_state))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'handler_state))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'handler_state))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'docking_state))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'docking_state))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'type))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'type))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <state_monitor>) istream)
  "Deserializes a message object of type '<state_monitor>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'system_state) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'system_state) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'door_state) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'door_state) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'handler_state) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'handler_state) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'docking_state) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'docking_state) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'type) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'type) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<state_monitor>)))
  "Returns string type for a message object of type '<state_monitor>"
  "smart_cargo_package/state_monitor")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'state_monitor)))
  "Returns string type for a message object of type 'state_monitor"
  "smart_cargo_package/state_monitor")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<state_monitor>)))
  "Returns md5sum for a message object of type '<state_monitor>"
  "155a94a5ff2117e15f117d9248317262")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'state_monitor)))
  "Returns md5sum for a message object of type 'state_monitor"
  "155a94a5ff2117e15f117d9248317262")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<state_monitor>)))
  "Returns full string definition for message of type '<state_monitor>"
  (cl:format cl:nil "string system_state  # smart_cargo 현재 동작 상태~%string door_state    # 적재함 Door 현재 동작 상태~%string handler_state # Handler 현재 동작 상태~%string docking_state # IF_docking Message 수신 상태~%string type          # Message Object~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'state_monitor)))
  "Returns full string definition for message of type 'state_monitor"
  (cl:format cl:nil "string system_state  # smart_cargo 현재 동작 상태~%string door_state    # 적재함 Door 현재 동작 상태~%string handler_state # Handler 현재 동작 상태~%string docking_state # IF_docking Message 수신 상태~%string type          # Message Object~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <state_monitor>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'system_state))
     4 (cl:length (cl:slot-value msg 'door_state))
     4 (cl:length (cl:slot-value msg 'handler_state))
     4 (cl:length (cl:slot-value msg 'docking_state))
     4 (cl:length (cl:slot-value msg 'type))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <state_monitor>))
  "Converts a ROS message object to a list"
  (cl:list 'state_monitor
    (cl:cons ':system_state (system_state msg))
    (cl:cons ':door_state (door_state msg))
    (cl:cons ':handler_state (handler_state msg))
    (cl:cons ':docking_state (docking_state msg))
    (cl:cons ':type (type msg))
))
