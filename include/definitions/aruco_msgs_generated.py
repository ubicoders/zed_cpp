# automatically generated by the FlatBuffers compiler, do not modify

# namespace: ArUco

import flatbuffers
from flatbuffers.compat import import_numpy
np = import_numpy()

class Point2D(object):
    __slots__ = ['_tab']

    @classmethod
    def SizeOf(cls):
        return 8

    # Point2D
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

    # Point2D
    def X(self): return self._tab.Get(flatbuffers.number_types.Float32Flags, self._tab.Pos + flatbuffers.number_types.UOffsetTFlags.py_type(0))
    # Point2D
    def Y(self): return self._tab.Get(flatbuffers.number_types.Float32Flags, self._tab.Pos + flatbuffers.number_types.UOffsetTFlags.py_type(4))

def CreatePoint2D(builder, x, y):
    builder.Prep(4, 8)
    builder.PrependFloat32(y)
    builder.PrependFloat32(x)
    return builder.Offset()


class Marker(object):
    __slots__ = ['_tab']

    @classmethod
    def GetRootAs(cls, buf, offset=0):
        n = flatbuffers.encode.Get(flatbuffers.packer.uoffset, buf, offset)
        x = Marker()
        x.Init(buf, n + offset)
        return x

    @classmethod
    def GetRootAsMarker(cls, buf, offset=0):
        """This method is deprecated. Please switch to GetRootAs."""
        return cls.GetRootAs(buf, offset)
    # Marker
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

    # Marker
    def Id(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            return self._tab.Get(flatbuffers.number_types.Int32Flags, o + self._tab.Pos)
        return 0

    # Marker
    def Corners(self, j):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        if o != 0:
            x = self._tab.Vector(o)
            x += flatbuffers.number_types.UOffsetTFlags.py_type(j) * 8
            obj = Point2D()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

    # Marker
    def CornersLength(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        if o != 0:
            return self._tab.VectorLen(o)
        return 0

    # Marker
    def CornersIsNone(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        return o == 0

def MarkerStart(builder):
    builder.StartObject(2)

def MarkerAddId(builder, id):
    builder.PrependInt32Slot(0, id, 0)

def MarkerAddCorners(builder, corners):
    builder.PrependUOffsetTRelativeSlot(1, flatbuffers.number_types.UOffsetTFlags.py_type(corners), 0)

def MarkerStartCornersVector(builder, numElems):
    return builder.StartVector(8, numElems, 4)

def MarkerEnd(builder):
    return builder.EndObject()



class ImageMarkers(object):
    __slots__ = ['_tab']

    @classmethod
    def GetRootAs(cls, buf, offset=0):
        n = flatbuffers.encode.Get(flatbuffers.packer.uoffset, buf, offset)
        x = ImageMarkers()
        x.Init(buf, n + offset)
        return x

    @classmethod
    def GetRootAsImageMarkers(cls, buf, offset=0):
        """This method is deprecated. Please switch to GetRootAs."""
        return cls.GetRootAs(buf, offset)
    # ImageMarkers
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

    # ImageMarkers
    def ImageName(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            return self._tab.String(o + self._tab.Pos)
        return None

    # ImageMarkers
    def Markers(self, j):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        if o != 0:
            x = self._tab.Vector(o)
            x += flatbuffers.number_types.UOffsetTFlags.py_type(j) * 4
            x = self._tab.Indirect(x)
            obj = Marker()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

    # ImageMarkers
    def MarkersLength(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        if o != 0:
            return self._tab.VectorLen(o)
        return 0

    # ImageMarkers
    def MarkersIsNone(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        return o == 0

def ImageMarkersStart(builder):
    builder.StartObject(2)

def ImageMarkersAddImageName(builder, imageName):
    builder.PrependUOffsetTRelativeSlot(0, flatbuffers.number_types.UOffsetTFlags.py_type(imageName), 0)

def ImageMarkersAddMarkers(builder, markers):
    builder.PrependUOffsetTRelativeSlot(1, flatbuffers.number_types.UOffsetTFlags.py_type(markers), 0)

def ImageMarkersStartMarkersVector(builder, numElems):
    return builder.StartVector(4, numElems, 4)

def ImageMarkersEnd(builder):
    return builder.EndObject()



class StereoImageMarkers(object):
    __slots__ = ['_tab']

    @classmethod
    def GetRootAs(cls, buf, offset=0):
        n = flatbuffers.encode.Get(flatbuffers.packer.uoffset, buf, offset)
        x = StereoImageMarkers()
        x.Init(buf, n + offset)
        return x

    @classmethod
    def GetRootAsStereoImageMarkers(cls, buf, offset=0):
        """This method is deprecated. Please switch to GetRootAs."""
        return cls.GetRootAs(buf, offset)
    # StereoImageMarkers
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

    # StereoImageMarkers
    def LeftImage(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            x = self._tab.Indirect(o + self._tab.Pos)
            obj = ImageMarkers()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

    # StereoImageMarkers
    def RightImage(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        if o != 0:
            x = self._tab.Indirect(o + self._tab.Pos)
            obj = ImageMarkers()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

def StereoImageMarkersStart(builder):
    builder.StartObject(2)

def StereoImageMarkersAddLeftImage(builder, leftImage):
    builder.PrependUOffsetTRelativeSlot(0, flatbuffers.number_types.UOffsetTFlags.py_type(leftImage), 0)

def StereoImageMarkersAddRightImage(builder, rightImage):
    builder.PrependUOffsetTRelativeSlot(1, flatbuffers.number_types.UOffsetTFlags.py_type(rightImage), 0)

def StereoImageMarkersEnd(builder):
    return builder.EndObject()



