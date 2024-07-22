;; Auto-generated. Do not edit!


(when (boundp 'smart_cargo_package::middle_control_msgs)
  (if (not (find-package "SMART_CARGO_PACKAGE"))
    (make-package "SMART_CARGO_PACKAGE"))
  (shadow 'middle_control_msgs (find-package "SMART_CARGO_PACKAGE")))
(unless (find-package "SMART_CARGO_PACKAGE::MIDDLE_CONTROL_MSGS")
  (make-package "SMART_CARGO_PACKAGE::MIDDLE_CONTROL_MSGS"))

(in-package "ROS")
;;//! \htmlinclude middle_control_msgs.msg.html


(defclass smart_cargo_package::middle_control_msgs
  :super ros::object
  :slots (_time_stamp _target_object _action ))

(defmethod smart_cargo_package::middle_control_msgs
  (:init
   (&key
    ((:time_stamp __time_stamp) (instance ros::time :init))
    ((:target_object __target_object) 0)
    ((:action __action) 0)
    )
   (send-super :init)
   (setq _time_stamp __time_stamp)
   (setq _target_object (round __target_object))
   (setq _action (round __action))
   self)
  (:time_stamp
   (&optional __time_stamp)
   (if __time_stamp (setq _time_stamp __time_stamp)) _time_stamp)
  (:target_object
   (&optional __target_object)
   (if __target_object (setq _target_object __target_object)) _target_object)
  (:action
   (&optional __action)
   (if __action (setq _action __action)) _action)
  (:serialization-length
   ()
   (+
    ;; time _time_stamp
    8
    ;; int32 _target_object
    4
    ;; int32 _action
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; time _time_stamp
       (write-long (send _time_stamp :sec) s) (write-long (send _time_stamp :nsec) s)
     ;; int32 _target_object
       (write-long _target_object s)
     ;; int32 _action
       (write-long _action s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; time _time_stamp
     (send _time_stamp :sec (sys::peek buf ptr- :integer)) (incf ptr- 4)  (send _time_stamp :nsec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _target_object
     (setq _target_object (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _action
     (setq _action (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get smart_cargo_package::middle_control_msgs :md5sum-) "8d58a37429769e2a5c482d5c6ba001eb")
(setf (get smart_cargo_package::middle_control_msgs :datatype-) "smart_cargo_package/middle_control_msgs")
(setf (get smart_cargo_package::middle_control_msgs :definition-)
      "time time_stamp      # Message 발행 시간 (ros::Time)
int32 target_object  # 대상 객체 H/W Index Enum
int32 action         # 명령 동작 Action Index Enum (홀수만 와야 한다)
")



(provide :smart_cargo_package/middle_control_msgs "8d58a37429769e2a5c482d5c6ba001eb")


