class Material {
	public:

		Material(float shininess, float amb[3], float diff[3], float spec[3]);
		void display();

	private:
		float shininess, ambient[3], diffuse[3], specular[3];
};