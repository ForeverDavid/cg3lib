/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 * @author Marco Livesu (marco.livesu@gmail.com)
 */

#ifndef CG3_MAINWINDOW_H
#define CG3_MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QSignalMapper>

#include <QProcess>
#ifdef __APPLE__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wredeclared-class-member"
#endif
#include <boost/bimap.hpp>
#ifdef __APPLE__
#pragma clang diagnostic pop
#endif

#include "glcanvas.h"
#include "utilities/loadersaver.h"
#include "utilities/consolestream.h"
#include "drawable_objects/drawable_mixed_objects.h"

class QToolBox;
class QVBoxLayout;
class QSpacerItem;

namespace cg3 {

class DrawableObject;
class PickableObject;
class DrawableContainer;

namespace viewer {

class GLCanvas;

namespace Ui {

class MainWindow;

} //namespace cg3::viewer::Ui

namespace internal {

class UiMainWindowRaiiWrapper;

} //namespace cg3::viewer::internal

/**
 * @brief Class that describes a Window containing an QGLViewer canvas and that manages
 * Managers and DrawableObjects.
 * @ingroup cg3viewer
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //Canvas:
    cg3::Point2Di getCanvasSize() const;

    //DrawableObjects for the Canvas
    void pushDrawableObject(
            const cg3::DrawableObject * obj,
            std::string checkBoxName = "",
            bool checkBoxChecked = true);
    bool deleteDrawableObject(const cg3::DrawableObject * obj);
    void setDrawableObjectVisibility(const cg3::DrawableObject * obj, bool visible);
    bool containsDrawableObject(const cg3::DrawableObject* obj);
    bool refreshDrawableObject(const cg3::DrawableObject* obj);
    bool setDrawableObjectName(
            const cg3::DrawableObject* obj,
            const std::string& newName);

    //Debug Objects
    void enableDebugObjects();
    void disableDebugObjects();

    //Window Options:
    void setFullScreen(bool);
    void toggleConsoleStream(); //work in progress...
    void keyPressEvent(QKeyEvent * event); //event options for keys pressed

    //Managers:
    unsigned int addManager(QFrame *f, std::string name, QToolBox *parent = nullptr);
    QFrame *getManager(unsigned int i);
    void renameManager(unsigned int i, std::string s);
    void setCurrentManager(unsigned int i);

signals:

    /**
     * @brief undoEvent
     * Conntect your slot with this signal in ordert to execute an action when the
     * user uses CTRL+Z in the MainWindow
     */
    void undoEvent();

    /**
     * @brief redoEvent
     * Conntect your slot with this signal in ordert to execute an action when the
     * user uses MAIUSC+CTRL+Z in the MainWindow
     */
    void redoEvent();

private slots:

    //Menu Actions
    void on_actionSave_Snapshot_triggered();
    void on_actionShow_Axis_triggered();
    void on_actionFull_Screen_toggled(bool arg1);
    void on_actionUpdate_Canvas_triggered();
    void on_actionFit_Scene_triggered();
    void on_actionChange_Background_Color_triggered();
    void on_actionSave_Point_Of_View_triggered();
    void on_actionLoad_Point_of_View_triggered();
    void on_actionShow_Hide_Dock_Widget_triggered();
    void on_actionLoad_Point_Of_View_from_triggered();
    void on_actionSave_Point_Of_View_as_triggered();
    void on_actionShow_Hide_Console_Stream_triggered();
    void on_actionEnable_Debug_Objects_triggered();
    void on_actionDisable_Debug_Objects_triggered();
    void on_action2D_Mode_triggered();
    void on_action3D_Mode_triggered();
    void on_actionReset_Point_of_View_triggered();
    void on_actionPerspective_Orthographic_Camera_Mode_triggered();

    void checkBoxClicked(int i);

    void addCheckBoxOfDrawableContainer(
            const DrawableContainer* cont,
            const std::string& objectName,
            bool vis);
    void removeCheckBoxOfDrawableContainer(const DrawableContainer* cont, unsigned int i);

private:

    struct ContainerProperties {
        QFrame* frame;
        std::vector<QCheckBox*> checkBoxes;
    };

    QCheckBox* pushDrawableObject(
            const cg3::DrawableObject * obj,
            QWidget* parent,
            std::string checkBoxName,
            bool checkBoxChecked);

    bool deleteDrawableObject(
            const cg3::DrawableObject * obj,
            QWidget* parent);

    //CheckBox management
    QCheckBox* createCheckBoxAndLinkSignal(
            const DrawableObject* obj,
            const std::string& checkBoxName,
            bool isChecked = true);

    QCheckBox* getCheckBoxDrawableObject(const DrawableObject* obj, int& idCheckBox);

    void removeCheckBox(QCheckBox* cb, int idCheckBox);

    // GUI
    //
    //Ui::MainWindow* ui;
    internal::UiMainWindowRaiiWrapper* ui;
    std::vector<QFrame*> managers;
    ConsoleStream* consoleStream;
    QVBoxLayout* scrollAreaLayout;
    cg3::viewer::LoaderSaver povLS;

    // Mesh Stack
    //
    QSignalMapper* checkBoxMapper;
    std::map<int, QCheckBox*> checkBoxes;
    boost::bimap<int, const cg3::DrawableObject*> mapObjects;
    int nCheckBoxes;
    std::map<const cg3::DrawableContainer*, ContainerProperties > containerFrames;
    bool first;
    bool debugObjectsEnabled;
    QSpacerItem* m_spacer;

public:

    GLCanvas& canvas; /** @brief Public member of type cg3::viewer::GLCanvas that allows
                          to manage the canvas contained in the MainWindow. */
    cg3::DrawableMixedObjects debugObjects; /** @brief Public member of type
                                                cg3::DrawableMixedObjects that allows to
                                                manage the debug objects that can be shown
                                                in the canvas. In order to use this member,
                                                remember to call the function
                                                "MainWindow::enableDebugObjects()".*/
};

} //namespace cg3::viewer
} //namespace cg3

#endif // CG3_MAINWINDOW_H
