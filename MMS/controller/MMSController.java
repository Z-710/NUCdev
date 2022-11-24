package controller;


import au.edu.uts.ap.javafx.Controller;
import java.text.DecimalFormat;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.TableCell;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import model.MMS;
import model.*;


public class MMSController extends Controller<MMS>{
    @FXML private TableView<MMSreport> mmsTv;
    @FXML private TableColumn<MMSreport,Double> expensetc; 
    @FXML private TableColumn<MMSreport,Double> creditstc; 
    @FXML private TableColumn<MMSreport,Double> ptctc;
    @FXML private TableColumn<MMSreport,Double> dollartc;
    private static final DecimalFormat df = new DecimalFormat("0.00");
    private static final DecimalFormat dollarf = new DecimalFormat("$0.00");
    public  MMS getMMS(){return model;}
    private ObservableList<MMSreport> getMMSList(){return getMMS().reports();}
    @FXML private Label totalexpense;
    @FXML private Label avggas;
    @FXML private Label avgpay;
    @FXML private Label totalcredits;
    @FXML private Label avgdeduction;
    @FXML private Label dollaravailable;
    
    @FXML private void initialize() {
        mmsTv.setItems(getMMSList());
        totalexpense.setText("$"+df.format(getMMS().getTotalExpense()));
        avggas.setText(df.format(getMMS().getAvgGasdeductionRate()));
        avgpay.setText(df.format(getMMS().getAvgPayPerCredit()));
        totalcredits.setText(df.format(getMMS().getTotalCredits()));
        avgdeduction.setText(df.format(getMMS().getAvgdeductionRate()));
        dollaravailable.setText("$"+df.format(getMMS().getTotalDollarAvailable()));
        expensetc.setCellFactory(tc -> new TableCell<MMSreport,Double>(){
            @Override
            protected void updateItem(Double price, boolean empty) {
            super.updateItem(price, empty);
            if (empty) {
                setText(null);
            } else {
                setText(dollarf.format(price));
            }
            }
        });
        creditstc.setCellFactory(tc -> new TableCell<MMSreport,Double>(){
            @Override
            protected void updateItem(Double price, boolean empty) {
            super.updateItem(price, empty);
            if (empty) {
                setText(null);
            } else {
                setText(df.format(price));
            }
            }
        });
        ptctc.setCellFactory(tc -> new TableCell<MMSreport,Double>(){
            @Override
            protected void updateItem(Double price, boolean empty) {
            super.updateItem(price, empty);
            if (empty) {
                setText(null);
            } else {
                setText(df.format(price));
            }
            }
        });
        dollartc.setCellFactory(tc -> new TableCell<MMSreport,Double>(){
            @Override
            protected void updateItem(Double price, boolean empty) {
            super.updateItem(price, empty);
            if (empty) {
                setText(null);
            } else {
                setText(dollarf.format(price));
            }
            }
        });
    }
    @FXML private void handleClose(ActionEvent event) throws Exception {
        stage.close();
        }

}
