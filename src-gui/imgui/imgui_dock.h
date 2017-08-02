// -*-c++-*-
/*
  Copyright (c) 2017 Alberto Otero de la Roza
  <aoterodelaroza@gmail.com>, Robin Myhr <x@example.com>, Isaac
  Visintainer <x@example.com>, Richard Greaves <x@example.com>, Ángel
  Martín Pendás <angel@fluor.quimica.uniovi.es> and Víctor Luaña
  <victor@fluor.quimica.uniovi.es>.

  critic2 is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or (at
  your option) any later version.

  critic2 is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// Rewritten from: git@github.com:vassvik/imgui_docking_minimal.git

#ifndef IMGUI_DOCK_H
#define IMGUI_DOCK_H

#include "imgui.h"
#include "imgui_internal.h"
#include <list>

using namespace std;

namespace ImGui{

  struct Dock{
    enum Type_{Type_None,Type_Root,Type_Container,Type_Dock,Type_Horizontal,
	       Type_Vertical};
    enum Status_{Status_None,Status_Open,Status_Collapsed,Status_Closed,
		 Status_Dragged,Status_Docked};

    ImU32 id = 0; // id of the window
    char* label = nullptr; // window label
    ImVec2 pos; // position of the window
    ImVec2 size; // size of the window
    ImVec2 size_saved; // saved size (before docking for dockable window)
    ImRect tabbarrect = {}; // rectangle for the container tab bar
    ImVector<float> tabsx = {};
    ImGuiWindowFlags flags = 0; // flags for the window
    bool hidden = false; // whether a docked window is hidden
    bool hoverable = true; // whether a window responds to being hovered
    bool collapsed = false; // whether a docked window is collapsed
    bool collapsed_saved = false; // saved collapsed (before docking)
    Type_ type = Type_None; // type of docking window
    Status_ status = Status_None; // status of the docking window
    list<Dock *> stack = {}; // stack of docks at this level
    Dock *currenttab = nullptr; // currently selected tab
    Dock *parent = nullptr; // node immediately above current node
    Dock *root = nullptr; // root node of this tree
    ImGuiWindow* window = nullptr; // associated window
    bool *p_open = nullptr; // the calling routine open window bool
    bool control_window_this_frame = false; // the pos, size, etc. change window's attributes this frame
    int nchild = 0; // number of children (to generate labels)
    bool automatic = false; // whether this dock was not generated by the user
    float tabdz = 0.f; // tab bar height for a container

    Dock(): pos(0,0), size(-1,-1), size_saved(-1,-1) {};
    ~Dock(){ MemFree(label);}

    // Is the mouse hovering the tab bar of this dock?
    bool IsMouseHoveringTabBar();
    // Is the mouse hovering the drop edges of a container?  Returns
    // the edge id.
    int IsMouseHoveringEdge();
    // Get the nearest tab border in the tab
    int getNearestTabBorder();
    // Show the drop targets for this window (full window)
    void showDropTargetFull();
    // Show the drop targets for this window (on the tab bar)
    void showDropTargetOnTabBar();
    // Show the drop targets on the edge of the container.
    void showDropTargetEdge(int edge);
    // Add a new dock to a container (at position ithis)
    void newDock(Dock *dnew, int ithis = -1);
    // Add a new dock to a docked container (child of
    // rootcontainer). Return the new container.
    void newDockRoot(Dock *dnew, int iedge);
    // Replace this dock (part of a root container tree) with a
    // horizontal (type==Type_Horizontal) or vertical
    // (type==Type_Vertical) container. The new container has the
    // current dock plus dcont (if null, dcont is allocated). The new
    // container is placed before (before==true) or after (false) the
    // old one.
    Dock *OpRoot_ReplaceHV(Type_ type,bool before,Dock *dcont=nullptr);
    // Add a new container (dcont) to the horizontal/vertical parent
    // of this dock.  If !dcont, it is allocated. The new container is
    // placed before (before==true) or after (false) the old one.
    Dock *OpRoot_AddToHV(bool before,Dock *dcont=nullptr);
    // Fill a root container with at least one container
    void OpRoot_FillEmpty();
    // Kill a dock. If a parent is given, elminiate it from the stack
    // if present. If replacement is given, replace it in the stack.
    void killDock(Dock *parent=nullptr, Dock *replacement=nullptr);
    // Kill an automatic container if it is empty
    void killContainerMaybe();
    // Draw container
    void drawContainer(bool allowresize);
    // Traverse the tree of a root container and draw all containers in it
    void drawRootContainer(Dock* root);
    // Traverse the tree of a root container and draw all bars in it
    void drawRootContainerBars(Dock* root);
    // Draw the tab bar of a tabbed container
    void drawTabBar();
    // Clear all docked windows from a container
    void clearContainer();
    // Kill a root container
    void clearRootContainer();
    // focus a Container and maybe move its docked window up
    void focusContainer();
    // Hide the window corresponding to a docked tab in container dcont
    void hideTabWindow(Dock *dcont);
    // Hide the window corresponding to a docked tab in container dcont
    // If noresize, forbid resizing the shown window.
    void showTabWindow(Dock *dcont, bool noresize);
    
  }; // struct Dock

  // Create a root container with the given label. If p_open, with a
  // close button.  Extra window flags are passed to the container
  // window.
  Dock *RootContainer(const char* label, bool* p_open=nullptr, ImGuiWindowFlags extra_flags=0);

  // Create a container with the given label. If p_open, with a close
  // button.  Extra window flags are passed to the container window.
  Dock *Container(const char* label, bool* p_open=nullptr, ImGuiWindowFlags extra_flags=0);

  // Create/end a window that can be docked to a container. If p_open,
  // with a close button. Extra window flags are passed to the
  // container window. If a container pointer is passed, dock to that
  // container in the first pass.
  bool BeginDock(const char* label, bool* p_open=nullptr, ImGuiWindowFlags extra_flags=0, Dock *oncedock=nullptr);
  void EndDock();

  // Free the memory occupied by the docks and the dock hash table
  void ShutdownDock();

  // Print information about the current known docks. Debug only.
  void Print();
  
} // namespace ImGui
#endif