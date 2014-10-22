
set(property_SRCS
  propertytree.cpp
  propertyitemmodel.cpp
  propertyitem.cpp
  propertywidget.cpp
  screenproperties.cpp
  screenitemproperties.cpp
  screenelementproperties.cpp
  actionproperties.cpp
  propertylist.cpp
  propertyitemdelegate.cpp
)

set(property_MOCS
  propertytree.h
  propertyitemmodel.h
  propertywidget.h
  screenproperties.h
  screenitemproperties.h
  screenelementproperties.h
  actionproperties.h
  propertylist.h
  propertyitemdelegate.h
)
QT4_WRAP_CPP(MOCS ${property_MOCS})

add_library(yggdrasil_property STATIC ${property_SRCS} ${MOCS})
