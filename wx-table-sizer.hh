#ifndef __GT__WX_TABLE_SIZER
#define  __GT__WX_TABLE_SIZER
#include <wx/sizer.h>
#include <vector.h>

class table_wx : public wxBoxSizer
{
protected:
  vector<wxBoxSizer*> hboxes;
  int m_cols;
  int m_rows;
  int m_current_row;
  int m_current_col;
  int m_total_hboxes;
public:
  table_wx(int cols=1, int rows=1);
  ~table_wx();
  bool set_cols(int cols);
  bool set_rows(int rows);
  bool resize(int cols, int rows);
  int get_cols();
  int get_rows();
  bool add_rows(int rows=1);
  bool add_cols(int cols=1);
  bool push_back(wxWindow* win);
  bool re_init(int cols, int rows);
  bool set_current_col(int col);
  bool set_current_row(int row);
protected:
  bool add_one_hbox();
};


#endif
