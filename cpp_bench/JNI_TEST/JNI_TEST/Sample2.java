import com.hp.hpl.jena.rdf.model.*;
public class Sample2 extends Object{
	public String name;
	
	public static String sayHello(String name) {
		/*Resource johnSmith = model.createResource(personURI);
		Property pFullName = model.createProperty(fullNameURI, "fullName");
		johnSmith.addProperty(pFullName, fullName);*/
		return "Hello, " + name + "!";
	}
	
	public String sayHello() {
		String personURI = "http://somewhere/JohnSmith/";
		String fullNameURI = "http://somewhere/fullname/";
		String givenName = "John";
		String familyName = "Smith";
		String fullName = givenName + " " + familyName;
		Model model = ModelFactory.createDefaultModel();
		return "Hello, " + name + "!";
	}
}