/*  This file is part of the KDE project
    Copyright (C) 1998, 1999 Torben Weis <weis@kde.org>
 
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
 
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
 
    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/     

#ifndef __konq_iconview_h__
#define __konq_iconview_h__

#include "kiconcontainer.h"
#include "konq_baseview.h"

#include <qtimer.h>
#include <qstrlist.h>

class KonqMainView;
class KonqKfmIconView;
class KonqPropsView;
class KDirLister;
class KFileItem;

/**
 * The Icon View for konqueror. Handles big icons (Horizontal mode) and
 * small icons (Vertical mode).
 * The "Kfm" in the name stands for file management since it shows files :)
 */
class KonqKfmIconView : public KIconContainer,
                        public KonqBaseView,
                        virtual public Konqueror::KfmIconView_skel
{
  Q_OBJECT
public:
  // C++
  KonqKfmIconView( KonqMainView *mainView = 0L );
  virtual ~KonqKfmIconView();

  virtual bool mappingOpenURL( Browser::EventOpenURL eventURL );
  virtual bool mappingFillMenuView( Browser::View::EventFillMenu_ptr viewMenu );
  virtual bool mappingFillMenuEdit( Browser::View::EventFillMenu_ptr editMenu );

  // IDL
  virtual void stop();
  virtual char *viewName() { return CORBA::string_dup("KonquerorKfmIconView"); }
  
  virtual char *url();
  virtual CORBA::Long xOffset();
  virtual CORBA::Long yOffset();

  virtual void openURL( const char* _url, int xOffset, int yOffset );
  
  //virtual void updateDirectory();

public slots:
  // IDL
  virtual void slotLargeIcons();
  virtual void slotSmallIcons();
  virtual void slotShowDot();
  virtual void slotSelect();
  virtual void slotSelectAll();

protected slots:
  // slots connected to the icon container
  virtual void slotMousePressed( KIconContainerItem* _item, const QPoint& _global, int _button );
  virtual void slotDoubleClicked( KIconContainerItem* _item, const QPoint& _global, int _button );
  virtual void slotReturnPressed( KIconContainerItem* _item, const QPoint& _global );
  virtual void slotDrop( QDropEvent*, KIconContainerItem*, QStringList& _formats );

  virtual void slotOnItem( KIconContainerItem* );
  
  // slots connected to the directory lister
  virtual void slotStarted( const QString & );
  virtual void slotCompleted();
  virtual void slotCanceled();
  virtual void slotUpdate();
  virtual void slotClear();
  virtual void slotNewItem( KFileItem * );
  virtual void slotDeleteItem( KFileItem * );

protected:  
  virtual void initConfig();

  /** The directory lister for this URL */
  KDirLister* m_dirLister;

  /** View properties */
  KonqPropsView * m_pProps;

  /**
   * Set to true while the constructor is running.
   * @ref #initConfig needs to know about that.
   */
  bool m_bInit;
  
  /** The view menu */
  OpenPartsUI::Menu_var m_vViewMenu;

  /** Set to true if the next slotUpdate needs to call setup() */
  bool bSetupNeeded;
  
  int m_iXOffset;
  int m_iYOffset;
  
  CORBA::Long m_idShowDotFiles;
  
  KonqMainView *m_pMainView;
};

#endif
