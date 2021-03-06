/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/


const QString& apm_edit_properties::getDefaultProvides(const QString &)
{
    my $type = shift;
    
    if ($type eq "Leap") {
        return "project";
    } else {
        return "model";
    }
}

void apm_edit_properties::init()
{
    my $model = $apm_edit::model;
    
    if (! defined($model)) {
      return;
    }

    Name->setText($model->name());

    type_asim = 0;
    type_hasim = 1;
    type_leap = 2;
  
    my $type = $model->type();

    if ($type eq "Asim") {
        typeComboBox->setCurrentItem(type_asim);
    } elsif ($type eq "HAsim") {
        typeComboBox->setCurrentItem(type_hasim);
    } elsif ($type eq "Leap") {
        typeComboBox->setCurrentItem(type_leap);
    } else {
        typeComboBox->setCurrentItem(type_leap);
    }
        
    Description->setText($model->description());
    Attributes->setText($model->attributes2string());

    Autoselect->setState($model->autoselect());

    Benchmark->setText($model->default_benchmark());
    RunOpts->setText($model->default_runopts());
    RootProvides->setText($model->provides());
    current_root_provides = $model->provides();
}


void apm_edit_properties::propertiesOk_clicked()
{
    my $model = $apm_edit::model;

    $model->name(Name->text());
    $model->type(typeComboBox->currentText());

    $model->description(Description->text());
    $model->set_attributes(Attributes->text());

    $model->autoselect(Autoselect->state());

    $model->default_benchmark(Benchmark->text());
    $model->default_runopts(RunOpts->text());
    
    $model->provides(RootProvides->text());

    this->accept();
}

void apm_edit_properties::propertiesHelp_clicked()
{
    Qt::WhatsThis::enterWhatsThisMode();
}

void apm_edit_properties::typeComboBox_activated( const QString & )
{
    my $newval = shift;
    my $old_default_provides = apm_edit_properties::getDefaultProvides(current_root_provides);
  
    if (RootProvides->text() eq $old_default_provides) {
        my $new_default_provides = apm_edit_properties::getDefaultProvides($newval);
        RootProvides->setText($new_default_provides);
    }
    current_root_provides = $newval;
}


