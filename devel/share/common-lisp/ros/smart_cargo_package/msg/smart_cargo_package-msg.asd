
(cl:in-package :asdf)

(defsystem "smart_cargo_package-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "action_complete_msgs" :depends-on ("_package_action_complete_msgs"))
    (:file "_package_action_complete_msgs" :depends-on ("_package"))
    (:file "middle_control_msgs" :depends-on ("_package_middle_control_msgs"))
    (:file "_package_middle_control_msgs" :depends-on ("_package"))
    (:file "sensor_signal_msgs" :depends-on ("_package_sensor_signal_msgs"))
    (:file "_package_sensor_signal_msgs" :depends-on ("_package"))
    (:file "state_monitor" :depends-on ("_package_state_monitor"))
    (:file "_package_state_monitor" :depends-on ("_package"))
  ))