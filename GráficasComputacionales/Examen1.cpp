positions.push_back(glm::vec2(0.0f, 0.0f));
colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));

for(float i = 0.0f; i < 361.0f; i += 1.0f) {
	positions.push_back(glm::vec2(
		glm::cos(glm::radians(i)), glm::sin(glm::radians(i))
	));


	colors.push_back(glm::vec3(
		cos(glm::radians(i)), 
		sin(glm::radians(i)),
		cos(glm::radians(i))*sin(glm::radians(i))));

	glDrawArrays(GL_TRIANGLE_FAN, 0, 362);

}