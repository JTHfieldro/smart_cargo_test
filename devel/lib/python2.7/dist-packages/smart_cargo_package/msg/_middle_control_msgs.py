# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from smart_cargo_package/middle_control_msgs.msg. Do not edit."""
import codecs
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import genpy

class middle_control_msgs(genpy.Message):
  _md5sum = "8d58a37429769e2a5c482d5c6ba001eb"
  _type = "smart_cargo_package/middle_control_msgs"
  _has_header = False  # flag to mark the presence of a Header object
  _full_text = """time time_stamp      # Message 발행 시간 (ros::Time)
int32 target_object  # 대상 객체 H/W Index Enum
int32 action         # 명령 동작 Action Index Enum (홀수만 와야 한다)"""
  __slots__ = ['time_stamp','target_object','action']
  _slot_types = ['time','int32','int32']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       time_stamp,target_object,action

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(middle_control_msgs, self).__init__(*args, **kwds)
      # message fields cannot be None, assign default values for those that are
      if self.time_stamp is None:
        self.time_stamp = genpy.Time()
      if self.target_object is None:
        self.target_object = 0
      if self.action is None:
        self.action = 0
    else:
      self.time_stamp = genpy.Time()
      self.target_object = 0
      self.action = 0

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_get_struct_2I2i().pack(_x.time_stamp.secs, _x.time_stamp.nsecs, _x.target_object, _x.action))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    if python3:
      codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      if self.time_stamp is None:
        self.time_stamp = genpy.Time()
      end = 0
      _x = self
      start = end
      end += 16
      (_x.time_stamp.secs, _x.time_stamp.nsecs, _x.target_object, _x.action,) = _get_struct_2I2i().unpack(str[start:end])
      self.time_stamp.canon()
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_get_struct_2I2i().pack(_x.time_stamp.secs, _x.time_stamp.nsecs, _x.target_object, _x.action))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    if python3:
      codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      if self.time_stamp is None:
        self.time_stamp = genpy.Time()
      end = 0
      _x = self
      start = end
      end += 16
      (_x.time_stamp.secs, _x.time_stamp.nsecs, _x.target_object, _x.action,) = _get_struct_2I2i().unpack(str[start:end])
      self.time_stamp.canon()
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_2I2i = None
def _get_struct_2I2i():
    global _struct_2I2i
    if _struct_2I2i is None:
        _struct_2I2i = struct.Struct("<2I2i")
    return _struct_2I2i
