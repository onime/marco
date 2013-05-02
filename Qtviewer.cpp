#include "Qtviewer.h"

Qtviewer::Qtviewer(string pname_scan,int pnum_scan,QWidget *parent) :QWidget(parent),name_scan(pname_scan), num_scan(pnum_scan)
{    
    QHBoxLayout *layout_button = new QHBoxLayout;
    QVBoxLayout *layout_main = new QVBoxLayout;
   
    QPushButton *next_page = new QPushButton(tr("&Next"));
    QPushButton *prev_page = new QPushButton(tr("&Prev"));
    QPushButton *first_page = new QPushButton(tr("&First"));
    QPushButton *last_page = new QPushButton(tr("&Last"));
    
    path_scan = PATH_SCANS+name_scan+'/'+Easylast::itos(num_scan);
    curr_page = 0;
    pages_scan = Easylast::list_pages_scan(path_scan);

    nb_page = pages_scan.size()-1;
    image_current = new QLabel("1");

    num_page = new LineNumPage;
   
    connect(next_page, SIGNAL(clicked()), this, SLOT(go_next_page()));
    connect(prev_page, SIGNAL(clicked()), this, SLOT(go_prev_page()));
    connect(first_page, SIGNAL(clicked()), this, SLOT(go_first_page()));
    connect(last_page, SIGNAL(clicked()), this, SLOT(go_last_page()));    
    connect(num_page,SIGNAL(returnPressed()),this,SLOT(go_to_page()));
 
    layout_button->addWidget(first_page);   
    layout_button->addWidget(prev_page);
    layout_button->addWidget(num_page);
    layout_button->addWidget(next_page);   
    layout_button->addWidget(last_page);
    //  layout_button->addStretch();

    image_current->setAlignment(Qt::AlignCenter);    
    layout_main->addWidget(image_current);
    layout_main->addItem(layout_button);

    setLayout(layout_main);   

} 

void Qtviewer::setQSummary(QSummaryManga *sum)
{
    SummManga = sum;
}

void  Qtviewer::keyPressEvent(QKeyEvent *event)
{
    QWidget::keyPressEvent(event);
    cout << event->key()<<endl;
    if(event->key() == 70)
    {
	image_current->showFullScreen();
	cout << "full"<<endl;
    }
    if(event->key() == 74)
	go_prev_page();

    if(event->key() == 77)
	go_next_page();
}


void Qtviewer::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    height_for_img =  image_current->height();
    width_for_img =  image_current->width();

    display_image_curr();
}


void Qtviewer::closeEvent(QCloseEvent *event)
 {
   
     event->accept();
     string cmd = "client_last --inc -t "+name_scan;
     system(cmd.c_str());
    
   
 }

void Qtviewer::go_next_page()
{
    if (curr_page < nb_page)
    {
	curr_page++;
	display_image_curr();
    }
    else
    {
	map<string,string> infos_dl = Easylast::parse_info("DL");
	
	if(atoi(infos_dl[name_scan].c_str()) > num_scan)
	{
	     string cmd = "client_last --VU --inc -t "+name_scan;
	     system(cmd.c_str());
	    
	     SummManga->setChap(num_scan+1);
	     new_scan();
	     
	}
    }
}

void Qtviewer::go_prev_page()
{
    if(curr_page > 0)
    {
	curr_page--;
	display_image_curr();
    }
}

void Qtviewer::go_first_page()
{
    curr_page = 0;
    display_image_curr();
}

void Qtviewer::go_last_page()
{
    curr_page = nb_page;
    display_image_curr();
}

void Qtviewer::go_to_page()
{
    QString p = num_page->text();
    string s = p.toStdString();

    curr_page = atoi(s.c_str())-1;
    display_image_curr();
}

void Qtviewer::new_scan()
{
    num_scan++;
    curr_page = 0;

    path_scan = PATH_SCANS+name_scan+'/'+Easylast::itos(num_scan);
    pages_scan = Easylast::list_pages_scan(path_scan);
    
    nb_page = pages_scan.size()-1;

    display_image_curr();

}

void Qtviewer::display_image(const string & path_img)
{
    QString qs = path_img.c_str();
    QPixmap img = QPixmap(qs);
    //int height_img = img.height();
    //int width_img = img.width();

    QPixmap scaled_img;

    scaled_img = img.scaledToHeight(height_for_img,Qt::SmoothTransformation);
    if(scaled_img.width() > width_for_img)
	scaled_img = img.scaledToWidth(width_for_img,Qt::SmoothTransformation);
    image_current->setPixmap(scaled_img);  
}

void Qtviewer::display_image_curr()
{
     string path_img = path_scan+'/'+pages_scan[curr_page];

    display_image(path_img);
    update_label();
}

void Qtviewer::update_label()
{
    num_page->setText(Easylast::itoqs(curr_page+1));
}

/*   for( map<string,int>::iterator ii=hash_info_scan.begin(); ii!=hash_info_scan.end(); ++ii)
     {
     cout << (*ii).first << ": " << (*ii).second << endl;
     }
*/
