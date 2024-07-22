;; Auto-generated. Do not edit!


(when (boundp 'smart_cargo_package::action_complete_msgs)
  (if (not (find-package "SMART_CARGO_PACKAGE"))
    (make-package "SMART_CARGO_PACKAGE"))
  (shadow 'action_complete_msgs (find-package "SMART_CARGO_PACKAGE")))
(unless (find-package "SMART_CARGO_PACKAGE::ACTION_COMPLETE_MSGS")
  (make-package "SMART_CARGO_PACKAGE::ACTION_COMPLETE_MSGS"))

(in-package "ROS")
;;//! \htmlinclude action_complete_msgs.msg.html


(defclass smart_cargo_package::action_complete_msgs
  :super ros::object
  :slots (_time_stamp _receive_object _action_object _complete_action _error_code ))

(defmethod smart_cargo_package::action_complete_msgs
  (:init
   (&key
    ((:time_stamp __time_stamp) (instance ros::time :init))
    ((:receive_object __receive_object) 0)
    ((:action_object __action_object) 0)
    ((:complete_action __complete_action) 0)
    ((:error_code __error_code) 0)
    )
   (send-super :init)
   (setq _time_stamp __time_stamp)
   (setq _receive_object (round __receive_object))
   (setq _action_object (round __action_object))
   (setq _complete_action (round __complete_action))
   (setq _error_code (round __error_code))
   self)
  (:time_stamp
   (&optional __time_stamp)
   (if __time_stamp (setq _time_stamp __time_stamp)) _time_stamp)
  (:receive_object
   (&optional __receive_object)
   (if __receive_object (setq _receive_object __receive_object)) _receive_object)
  (:action_object
   (&optional __action_object)
   (if __action_object (setq _action_object __action_object)) _action_object)
  (:complete_action
   (&optional __complete_action)
   (if __complete_action (setq _complete_action __complete_action)) _complete_action)
  (:error_code
   (&optional __error_code)
   (if __error_code (setq _error_code __error_code)) _error_code)
  (:serialization-length
   ()
   (+
    ;; time _time_stamp
    8
    ;; int32 _receive_object
    4
    ;; int32 _action_object
    4
    ;; int32 _complete_action
    4
    ;; int32 _error_code
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; time _time_stamp
       (write-long (send _time_stamp :sec) s) (write-long (send _time_stamp :nsec) s)
     ;; int32 _receive_object
       (write-long _receive_object s)
     ;; int32 _action_object
       (write-long _action_object s)
     ;; int32 _complete_action
       (write-long _complete_action s)
     ;; int32 _error_code
       (write-long _error_code s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; time _time_stamp
     (send _time_stamp :sec (sys::peek buf ptr- :integer)) (incf ptr- 4)  (send _time_stamp :nsec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _receive_object
     (setq _receive_object (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _action_object
     (setq _action_object (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _complete_action
     (setq _complete_action (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _error_code
     (setq _error_code (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get smart_cargo_package::action_complete_msgs :md5sum-) "8cfdf36b4b872dd50c9838483632d5fd")
(setf (get smart_cargo_package::action_complete_msgs :datatype-) "smart_cargo_package/action_complete_msgs")
(setf (get smart_cargo_package::action_complete_msgs :definition-)
      "time time_stamp       # Message 발행 시간 (ros::Time)
int32 receive_object    # 수신 객체 H/W Index Enum   <----- 꼭 필요한지 생각해보자 
int32 action_object    # 동작 객체 H/W Index Enum
int32 complete_action  # 완료 동작 Action Index Enum (짝수만 와야 한다)
int32 error_code       # Error-Code
")



(provide :smart_cargo_package/action_complete_msgs "8cfdf36b4b872dd50c9838483632d5fd")


