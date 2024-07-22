;; Auto-generated. Do not edit!


(when (boundp 'smart_cargo_package::sensor_signal_msgs)
  (if (not (find-package "SMART_CARGO_PACKAGE"))
    (make-package "SMART_CARGO_PACKAGE"))
  (shadow 'sensor_signal_msgs (find-package "SMART_CARGO_PACKAGE")))
(unless (find-package "SMART_CARGO_PACKAGE::SENSOR_SIGNAL_MSGS")
  (make-package "SMART_CARGO_PACKAGE::SENSOR_SIGNAL_MSGS"))

(in-package "ROS")
;;//! \htmlinclude sensor_signal_msgs.msg.html


(defclass smart_cargo_package::sensor_signal_msgs
  :super ros::object
  :slots (_time_stamp _index _value ))

(defmethod smart_cargo_package::sensor_signal_msgs
  (:init
   (&key
    ((:time_stamp __time_stamp) (instance ros::time :init))
    ((:index __index) 0)
    ((:value __value) 0)
    )
   (send-super :init)
   (setq _time_stamp __time_stamp)
   (setq _index (round __index))
   (setq _value (round __value))
   self)
  (:time_stamp
   (&optional __time_stamp)
   (if __time_stamp (setq _time_stamp __time_stamp)) _time_stamp)
  (:index
   (&optional __index)
   (if __index (setq _index __index)) _index)
  (:value
   (&optional __value)
   (if __value (setq _value __value)) _value)
  (:serialization-length
   ()
   (+
    ;; time _time_stamp
    8
    ;; int32 _index
    4
    ;; int32 _value
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; time _time_stamp
       (write-long (send _time_stamp :sec) s) (write-long (send _time_stamp :nsec) s)
     ;; int32 _index
       (write-long _index s)
     ;; int32 _value
       (write-long _value s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; time _time_stamp
     (send _time_stamp :sec (sys::peek buf ptr- :integer)) (incf ptr- 4)  (send _time_stamp :nsec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _index
     (setq _index (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _value
     (setq _value (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get smart_cargo_package::sensor_signal_msgs :md5sum-) "1c7a1b51f4e21ef105c7e6881304d350")
(setf (get smart_cargo_package::sensor_signal_msgs :datatype-) "smart_cargo_package/sensor_signal_msgs")
(setf (get smart_cargo_package::sensor_signal_msgs :definition-)
      "time time_stamp  # Message 발행 시간 (ros::Time)
int32 index       # DI/DO Signal Index Enum
int32 value      # Signal Value
")



(provide :smart_cargo_package/sensor_signal_msgs "1c7a1b51f4e21ef105c7e6881304d350")


