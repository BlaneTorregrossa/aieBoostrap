struct GLFWwindow
{

};


class Application
{
public:
	Application();
	virtual ~Application();
	void run(const char* title, int width, int height, bool fullscreen);	// run application with a given title resolution and if in fullscreen
	void setBackgroundColors(float red, float green, float blue, float alpha);
	void quit();
protected:
	virtual void startup();
	virtual void shutdown();
	virtual void update(float);
	virtual void draw();
private:
	GLFWwindow* m_window;
	bool m_check;
};

