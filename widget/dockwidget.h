#ifndef DOCKWIDGET_H
#define DOCKWIDGET_H

#include <QDockWidget>
#include <QWidget>

template <typename T>
class DockWidget : public QDockWidget
{
public:
    DockWidget()
    {
        m_widget = new T();
        setWidget(m_widget);
    }
    T* widget()
    {
        return m_widget;
    }
private:
    T* m_widget;
};

#endif // DOCKWIDGET_H
