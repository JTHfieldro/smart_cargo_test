;; Auto-generated. Do not edit!


(when (boundp 'smart_cargo_package::state_monitor)
  (if (not (find-package "SMART_CARGO_PACKAGE"))
    (make-package "SMART_CARGO_PACKAGE"))
  (shadow 'state_monitor (find-package "SMART_CARGO_PACKAGE")))
(unless (find-package "SMART_CARGO_PACKAGE::STATE_MONITOR")
  (make-package "SMART_CARGO_PACKAGE::STATE_MONITOR"))

(in-package "ROS")
;;//! \htmlinclude state_monitor.msg.html


(defclass smart_cargo_package::state_monitor
  :super ros::object
  :slots (_system_state _door_state _handler_state _docking_state _type ))

(defmethod smart_cargo_package::state_monitor
  (:init
   (&key
    ((:system_state __system_state) "")
    ((:door_state __door_state) "")
    ((:handler_state __handler_state) "")
    ((:docking_state __docking_state) "")
    ((:type __type) "")
    )
   (send-super :init)
   (setq _system_state (string __system_state))
   (setq _door_state (string __door_state))
   (setq _handler_state (string __handler_state))
   (setq _docking_state (string __docking_state))
   (setq _type (string __type))
   self)
  (:system_state
   (&optional __system_state)
   (if __system_state (setq _system_state __system_state)) _system_state)
  (:door_state
   (&optional __door_state)
   (if __door_state (setq _door_state __door_state)) _door_state)
  (:handler_state
   (&optional __handler_state)
   (if __handler_state (setq _handler_state __handler_state)) _handler_state)
  (:docking_state
   (&optional __docking_state)
   (if __docking_state (setq _docking_state __docking_state)) _docking_state)
  (:type
   (&optional __type)
   (if __type (setq _type __type)) _type)
  (:serialization-length
   ()
   (+
    ;; string _system_state
    4 (length _system_state)
    ;; string _door_state
    4 (length _door_state)
    ;; string _handler_state
    4 (length _handler_state)
    ;; string _docking_state
    4 (length _docking_state)
    ;; string _type
    4 (length _type)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _system_state
       (write-long (length _system_state) s) (princ _system_state s)
     ;; string _door_state
       (write-long (length _door_state) s) (princ _door_state s)
     ;; string _handler_state
       (write-long (length _handler_state) s) (princ _handler_state s)
     ;; string _docking_state
       (write-long (length _docking_state) s) (princ _docking_state s)
     ;; string _type
       (write-long (length _type) s) (princ _type s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _system_state
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _system_state (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _door_state
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _door_state (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _handler_state
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _handler_state (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _docking_state
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _docking_state (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _type
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _type (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(setf (get smart_cargo_package::state_monitor :md5sum-) "155a94a5ff2117e15f117d9248317262")
(setf (get smart_cargo_package::state_monitor :datatype-) "smart_cargo_package/state_monitor")
(setf (get smart_cargo_package::state_monitor :definition-)
      "string system_state  # smart_cargo 현재 동작 상태
string door_state    # 적재함 Door 현재 동작 상태
string handler_state # Handler 현재 동작 상태
string docking_state # IF_docking Message 수신 상태
string type          # Message Object
")



(provide :smart_cargo_package/state_monitor "155a94a5ff2117e15f117d9248317262")


