time time_stamp       # Message 발행 시간 (ros::Time)
int32 receive_object    # 수신 객체 H/W Index Enum   <----- 꼭 필요한지 생각해보자 
int32 action_object    # 동작 객체 H/W Index Enum
int32 complete_action  # 완료 동작 Action Index Enum (짝수만 와야 한다)
int32 error_code       # Error-Code.