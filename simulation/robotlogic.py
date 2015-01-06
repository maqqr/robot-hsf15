# -*- coding: utf-8 -*-
""" Wrapper for the robotlogic library.

Usage example:
robot = Robot('robotlogic.dll')
input = Input()
input.test_sensor_1 = 65.3
input.test_sensor_2 = 70.0
output = robot.think(input)
"""
import os
import re
import ctypes
from ctypes import Structure


def comment_remover(text):
    """ Removes C and C++ style comments.
        (http://stackoverflow.com/a/241506)"""
    def __replacer__(match):
        search = match.group(0)
        if search.startswith('/'):
            return " " # note: a space and not an empty string
        else:
            return search
    pattern = re.compile(
        r'//.*?$|/\*.*?\*/|\'(?:\\.|[^\\\'])*\'|"(?:\\.|[^\\"])*"',
        re.DOTALL | re.MULTILINE
    )
    return re.sub(pattern, __replacer__, text)


def parse_fields(filename):
    """ Very simple C structure parser.
        Returns {'structName': [('fieldType', 'fieldName'), ...], ...} """
    collected_structs = {}
    with open(filename, 'r') as filehandle:
        current_struct = []
        inside_struct = False
        lines = filehandle.readlines()
        for line in lines:
            if inside_struct:
                if line.startswith('{'):
                    # Ignore lines starting with {
                    continue
                elif line.startswith('}'):
                    # Struct ends. Name should be on this line.
                    name = line.split(' ')[1].strip('\r\n;')
                    collected_structs[name] = current_struct
                    inside_struct = False
                else:
                    # Line must be a struct field.
                    field = comment_remover(line).strip('\r\n\t ;')
                    current_struct.append(field.split(' '))
            else:
                if line.startswith('typedef struct'):
                    # Found a new struct.
                    current_struct = []
                    inside_struct = True
    return collected_structs


class MetaStruct(type(ctypes.Structure)):
    """ Automagic __repr__ and __str__ functions and _field_
        for ctypes.Structure subclasses. """
    def __new__(cls, clsname, clsbase, clsdict):
        newcls = super(MetaStruct, cls).__new__(cls, clsname, clsbase, clsdict)
        # Define __repr__ and __str__ for the class.
        def __auto_repr__(self):
            values = dict([(n, getattr(self, n)) for (n, _) in self._fields_])
            return "<%s %s>" % (self.__class__.__name__, str(values))
        newcls.__repr__ = __auto_repr__
        newcls.__str__ = lambda self: repr(self)
        # Find header files.
        root_folder = os.sep.join(os.path.realpath(__file__).split(os.sep)[:-2])
        header_path = os.path.join(root_folder, 'robotlogic', clsdict['__struct_file_name__'])
        # Get field names and types from the C header.
        # _field_ must be a list; [('fieldName', ctype), ...]
        all_fields = parse_fields(header_path)
        fields = all_fields.get(clsdict['__struct_name__'])
        newcls._fields_ = [(fname, getattr(ctypes, 'c_' + ftype)) \
                           for (ftype, fname) in fields]
        return newcls


class Input(Structure, metaclass=MetaStruct):
    """ Represents robot_input_t structure. """
    __struct_file_name__ = "robotlogic.h"
    __struct_name__ = "robot_input_t"


class Output(Structure, metaclass=MetaStruct):
    """ Represents robot_output_t structure. """
    __struct_file_name__ = "robotlogic.h"
    __struct_name__ = "robot_output_t"


class Robot(object):
    """ Interface for the robotlogic library. """
    def __init__(self, library_name):
        super(Robot, self).__init__()
        self.__library__ = None
        try:
            self.__library__ = ctypes.cdll.LoadLibrary(library_name)
        except OSError as err:
            print("\nYou probably need to use 32-bit version of Blender.\n")
            # Re-raise the exception.
            raise err
        self.__think_func__ = self.__library__.think
        self.__think_func__.argtypes = [Input]
        self.__think_func__.restype = Output

    def think(self, robot_input):
        """ Takes RobotInput and returns RobotOutput. """
        # ctypes raises ArgumentError if robot_input's type is not Input.
        return self.__think_func__(robot_input)
