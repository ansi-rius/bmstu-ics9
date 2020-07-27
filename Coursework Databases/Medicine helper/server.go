package main
import (
    "fmt"
    "database/sql"
     _ "github.com/denisenkom/go-mssqldb"
    "net/http"
    "html/template"
    "log"
    "strconv"
)
type ClassificationOfDiseases struct{
    ClassId int
    ClassName string
    ClassDescr string
}

type Diseases struct{

    DiseaseID string
    DiseaseName string
    AlternativeNames string
    RiskGroup string
    Cause  string
    Symptoms  string
    Diagnostics string
    Complications string
}

type Medicine struct{

    MedicineID string
    MedName string
    InternationalName string
    PharmacotherapeuticGroup string
    PharmacologicalProperties string
    Caution string
    HowToUse string
    Receipt string

    IDMedicineID string
    IDMedName string
    IDInternationalName string
    IDPharmacotherapeuticGroup string
    IDPharmacologicalProperties string
    IDCaution string
    IDHowToUse string
    IDReceipt string
}

type DiseaseAndClassView struct{

    ClassID int
    ClassName string
    DiseaseID string
    DiseaseName string

}

var server = "127.0.0.1"
var port = 1433
var user = "SA"
var password = "PtktysqXfq231Poz"
var d = "MEDICINE_HELPER2"

var db *sql.DB

var count = 1

func IndexHandler(w http.ResponseWriter, r *http.Request) {
    if r.Method == "POST" {
        err:=r.ParseForm()
        if err != nil {
            log.Println(err)
        }

        //disease
        diseaseName := r.FormValue("disease")
        //age
        age := r.FormValue("age")
        //state
        pregnant := r.FormValue("preg")
        contra := r.Form["contra"]
        features := r.Form["features"]
        medicines := r.Form["medicines"]

        getMedicine := ""
        getClass := "Select * From DiseaseAndClassView where DiseaseName=N'"+diseaseName+"'"
        
        if len(contra) != 0 {
            getMedicine = "Select MedicineID, MedName, InternationalName, PharmacotherapeuticGroup, PharmacologicalProperties, Caution, HowToUse, Receipt from DiseaseAndMedicineView where (DiseaseName=N'" + diseaseName+"' and ContradictionsFlag=1) except Select MedicineID, MedName, InternationalName, PharmacotherapeuticGroup, PharmacologicalProperties, Caution, HowToUse, Receipt from MedicineAndFeaturesAndContradictionsView where FeatureName = N'"+age+"' "
        } else {
            getMedicine = "Select MedicineID, MedName, InternationalName, PharmacotherapeuticGroup, PharmacologicalProperties, Caution, HowToUse, Receipt from DiseaseAndMedicineView where (DiseaseName=N'" + diseaseName+"' and ContradictionsFlag=1) except Select MedicineID, MedName, InternationalName, PharmacotherapeuticGroup, PharmacologicalProperties, Caution, HowToUse, Receipt from MedicineAndFeaturesView where FeatureName = N'"+age+"' "
        }
        getDisease := "Select DiseaseID, DiseaseName, AlternativeNames, RiskGroup, Cause, Symptoms, Diagnostics, Complications from Diseases where DiseaseName = N'"+diseaseName+"'"
    
        //state

        getMedicine += "or FeatureName=N'"+pregnant+"'"

        for i:=0; i<len(contra); i++ {
            getMedicine += "or DiseaseName=N'"+contra[i]+"'"
        }

        for i:=0; i<len(features); i++ {
            getMedicine += "or FeatureName=N'"+features[i]+"'"
        }


        
        //log.Println(feeding)
        /*val := r.FormValue("insult")
        val2 := r.FormValue("tub")
        if val == "on" {
            diseaseName = "Инсульт, не уточненный как кровоизлияние или инфаркт"
        } else
        if val2 == "on" {
            diseaseName = "Туберкулез органов дыхания, подтвержденный бактериологически и гистологически"
        }*/


        
        log.Println(getMedicine)


        rows, err := db.Query(getClass)
        if err != nil {
            log.Println(err)
        }
        //log.Println(rows)
        
        defer rows.Close()
        
        classificationsOfDiseases := []DiseaseAndClassView{}
         
        for rows.Next(){
            p := DiseaseAndClassView{}
            err := rows.Scan(&p.ClassID, &p.ClassName, &p.DiseaseID, &p.DiseaseName)
            if err != nil{
                fmt.Println(err)
                continue
            }
            //fmt.Fprintf(w, "%s", p)
            classificationsOfDiseases = append(classificationsOfDiseases, p)
        }

        rows1, err := db.Query(getMedicine)
        if err != nil {
            log.Println(err)
        }
         
        defer rows1.Close()
        
        medicine := []Medicine{}


         
        for rows1.Next(){
            m := Medicine{}
            err := rows1.Scan(&m.MedicineID, &m.MedName, &m.InternationalName, &m.PharmacotherapeuticGroup,
                &m.PharmacologicalProperties, &m.Caution, &m.HowToUse, &m.Receipt)
            if err != nil{
                log.Println(err)
                continue
            }
            
            m.IDMedicineID = "hd-"+strconv.Itoa(count)
            count++
            m.IDMedName = "hd-"+strconv.Itoa(count)
            count++
            m.IDInternationalName = "hd-"+strconv.Itoa(count)
            count++
            m.IDPharmacotherapeuticGroup = "hd-"+strconv.Itoa(count)
            count++
            m.IDPharmacologicalProperties = "hd-"+strconv.Itoa(count)
            count++
            m.IDCaution = "hd-"+strconv.Itoa(count)
            count++
            m.IDHowToUse = "hd-"+strconv.Itoa(count)
            count++
            m.IDReceipt = "hd-"+strconv.Itoa(count)
            count++


            //fmt.Fprintf(w, "%s", p)
            if contains(medicines, m.MedicineID) {
                medicine = append(medicine, m)
            }
        }


        rows2, err := db.Query(getDisease)
        if err != nil {
            log.Println(err)
        }
         
        defer rows2.Close()
        
        diseases := []Diseases{}


         
        for rows2.Next(){
            d := Diseases{}
            err := rows2.Scan(&d.DiseaseID, &d.DiseaseName, &d.AlternativeNames, &d.RiskGroup, &d.Cause, &d.Symptoms, &d.Diagnostics, &d.Complications)
            if err != nil{
                log.Println(err)
                continue
            }
            //fmt.Fprintf(w, "%s", p)
            diseases = append(diseases, d)

        }



        if len(diseases) == 0 {
            //tut budet oshibka
        }
        
        tmpl0, _ := template.ParseFiles("templates/index.html")
        tmpl0.Execute(w, classificationsOfDiseases)

        tmpl, _ := template.ParseFiles("templates/create0.html")
        tmpl.Execute(w, classificationsOfDiseases)

        tmpl1, _ := template.ParseFiles("templates/create1-l.html")
        tmpl1.Execute(w, medicine)

        tmpl2, _ := template.ParseFiles("templates/create2-l.html")
        tmpl2.Execute(w, diseases)
        
        //http.Redirect(w,r,"/create",301)

    } else {
        http.ServeFile(w,r, "templates/index.html")
    }
}

func contains(s []string, e string) bool {
    for _, a := range s {
        if a == e {
            return true
        }
    }
    return false
}
 
func main() {
    fs := http.FileServer(http.Dir("static/"))
    http.Handle("/static/", http.StripPrefix("/static/", fs))

    connString := fmt.Sprintf("server=%s;user id=%s;password=%s;port=%d;database=%s;",
        server, user, password, port, d)
      
    var err error
    db, err = sql.Open("sqlserver", connString)
     
    if err != nil {
        log.Println(err)
    }
    //database = db
    defer db.Close()
    http.HandleFunc("/", IndexHandler)
 
    fmt.Println("Server is listening...")
    http.ListenAndServe(":8182", nil)
}