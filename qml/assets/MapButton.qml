import QtQuick 2.4
import Sailfish.Silica 1.0


/*
  Шаблон кнопки на карте (увеличить, уменьшить и т.п.)
*/
Button {
    property string sourceIcon

    width: height
    color: Theme.highlightDimmerColor
    border {
        color: Theme.rgba(color, Theme.opacityFaint)
        highlightColor: Theme.rgba(highlightBackgroundColor,
                                   Theme.highlightBackgroundOpacity)
    }
    icon.source: sourceIcon.arg(Theme.highlightDimmerColor)
}
