package controller;

import au.edu.uts.ap.javafx.Controller;
import java.text.DecimalFormat;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import model.Membership;

public class MMSlipController extends Controller<Membership>{
    public  Membership getMembership(){return model;}
    @FXML private Label creditLbl;
    @FXML private Label expenseLbl;
    @FXML private Label gasdeductionLbl;
    @FXML private Label paypercreditLbl;
    @FXML private Label dollaravailableLbl;
    @FXML private Label deductionLbl;
    private static final DecimalFormat df = new DecimalFormat("0.00");

    @FXML private void initialize() {
        
        creditLbl.setText(df.format(getMembership().gettotalCredits()));
        expenseLbl.setText("$"+df.format(getMembership().getexpense()));
        gasdeductionLbl.setText(df.format(getMembership().getGasdeductionRate()));
        paypercreditLbl.setText(df.format(getMembership().getPayPerCredit()));
        dollaravailableLbl.setText("$"+df.format(getMembership().getDollarAvailable()));
        deductionLbl.setText(df.format(getMembership().getdeductionRate()));
    }
    @FXML private void handleClose(ActionEvent event) throws Exception {
        stage.close();
        }

}
