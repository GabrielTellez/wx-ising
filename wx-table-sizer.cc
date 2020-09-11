#include "wx-table-sizer.hh"

bool table_wx::set_rows(int rows)
{
  if (rows<1) return false;
  m_rows=rows;
  return true;
}

bool table_wx::set_cols(int cols)
{
  if (cols<1) return false;
  m_cols=cols;
  return true;
}

bool table_wx::resize(int cols, int rows)
{
  if (cols<1) return false;
  if (rows<1) return false;
  m_cols=cols;
  m_rows=rows;
  return true;
}

int table_wx::get_cols()
{
  return m_cols;
}

int table_wx::get_rows()
{
  return m_rows;
}

// constructor

table_wx::table_wx(int cols, int rows) :
  wxBoxSizer(wxVERTICAL),
  m_total_hboxes(0)
{
  if(rows<1) {
    rows=1;
    cerr<< "table_wx ctor: rows <1 setting m_rows=1\n";
  }
  if(cols<1) {
    cerr<< "table_wx ctor: cols <1 setting m_cols=1\n";
    cols=1;
  }
  m_cols=cols;
  m_rows=rows;
  m_current_row=0;
  m_current_col=-1;
  add_one_hbox();
}

// destructor

table_wx::~table_wx()
{
  /*
  for(int i=0; i<=m_current_row;i++) {
     delete hboxes[i];
  }
  */
}

bool table_wx::add_one_hbox()
{
  if(m_total_hboxes>m_rows) {
    return false;
  }
  hboxes.push_back(new wxBoxSizer(wxHORIZONTAL));
  m_total_hboxes++;
  this->Add(hboxes[m_total_hboxes-1],
	    1,                // make vertically stretchable
	    wxGROW ); 
  return true;
}

bool table_wx::add_rows(int rows)
{
  if(rows<=0) return false;
  m_rows+=rows;
  return true;
}

bool table_wx::add_cols(int cols)
{
  if(cols<=0) return false;
  m_cols+=cols;
  return true;
}

bool table_wx::push_back(wxWindow* win)
{
  if((m_current_row>=m_rows-1)&&(m_current_col>=m_cols-1)) return false;
  if(m_current_col>=m_cols-1) {
    m_current_row++;
    m_current_col=-1;
    if(m_current_row>=m_total_hboxes) {
      if(!(add_one_hbox())) {
	cout <<"table_wx::push_back: couldn't add_one_box\n";
      }
    }
  }
  m_current_col++;
  hboxes[m_current_row]->Add(win,
			     1,   // make horizontally stretchable
			     wxGROW ); 
  return true;
}

bool table_wx::set_current_row(int row)
{
  if ((row>=m_rows)||(row<-1)) return false;
  m_current_row=row;
  return true;
}

bool table_wx::set_current_col(int col)
{
  if((col>=m_cols)||(col<-1)) return false;
  m_current_col=col;
  return true;
}

bool table_wx::re_init(int cols, int rows)
{
  // Remove all buttons
  for (int nb=0; nb<=m_current_row;nb++) {
    for(int i=0;i<m_cols;i++) {
      if(!(hboxes[nb]->Remove(0))) {
	cout << "Error removing button row="<< nb <<" col="<<i<<"\n";
      }
    }
  }

  // Remove hboxes
  for(int i=0;i<m_total_hboxes;i++) {
    if(!(Remove(0))) {
    }
  }
  hboxes.erase(hboxes.begin(), hboxes.end());

  if(!resize(cols, rows)) {
    return false;
  }
  
  set_current_col(-1);
  m_total_hboxes=0;
  add_one_hbox();
  set_current_row(0);
  Layout();
  return true;
}

