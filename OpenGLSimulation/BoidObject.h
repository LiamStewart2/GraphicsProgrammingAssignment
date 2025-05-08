#pragma once

#include "Object.h"

class BoidObject : public Object
{
public:
	BoidObject(Mesh* _mesh, Material* _material, Transform _transform, const char* _name = "boid") : Object(_mesh, _material, _transform, _name)
	{

	}

	void SetReferenceToBoids(std::vector<BoidObject*>* _boids) { boids = _boids; }

	void Update() override
	{
		std::vector<BoidObject*> boidsInRange = std::vector<BoidObject*>();
		GetBoidsInRange(boidsInRange);

		Seperation(&boidsInRange);
		Alignment(&boidsInRange);
		Coherence(&boidsInRange);


		if (transform.Position.x < boundingDistance)
			velocity.x += turnFactor;
		if (transform.Position.x > boundingDistance)
			velocity.x -= turnFactor;

		if (transform.Position.y < 10)
			velocity.y += turnFactor;
		if (transform.Position.y > boundingDistance + 10)
			velocity.y -= turnFactor;

		if (transform.Position.z < -boundingDistance)
			velocity.z += turnFactor;
		if (transform.Position.z > boundingDistance)
			velocity.z -= turnFactor;


		speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y + velocity.z * velocity.z);
		if (speed > maxSpeed)
		{
			velocity.x = (velocity.x / speed) * maxSpeed;
			velocity.y = (velocity.y / speed) * maxSpeed;
			velocity.z = (velocity.z / speed) * maxSpeed;
		}
		if (speed < minSpeed)
		{
			velocity.x = (velocity.x / speed) * minSpeed;
			velocity.y = (velocity.y / speed) * minSpeed;
			velocity.z = (velocity.z / speed) * minSpeed;
		}

		transform.Position = transform.Position + velocity;
	}

private:
	std::vector<BoidObject*>* boids = nullptr;

	// Boids avoid eachother to not overlap
	void Seperation(std::vector<BoidObject*>* boidsInRange)
	{
		close = Vector3f(0, 0, 0);
		for (int i = 0; i < boidsInRange->size(); i++)
			close = close + (transform.Position - boidsInRange->at(i)->transform.Position);
		velocity.x += close.x * seperation;
		velocity.y += close.y * seperation;
		velocity.z += close.z * seperation;
	}
	// Boids align with one another to form groups
	void Alignment(std::vector<BoidObject*>* boidsInRange)
	{
		velocityAverage = Vector3f(0, 0, 0);
		for (int i = 0; i < boidsInRange->size(); i++)
			velocityAverage = velocityAverage + boidsInRange->at(i)->velocity;
		velocityAverage.x = velocityAverage.x / boidsInRange->size();
		velocityAverage.y = velocityAverage.y / boidsInRange->size();
		velocityAverage.z = velocityAverage.z / boidsInRange->size();

		velocity.x += (velocityAverage.x - velocity.x) * alighnment;
		velocity.y += (velocityAverage.y - velocity.y) * alighnment;
		velocity.z += (velocityAverage.z - velocity.z) * alighnment;
	}
	// Boids steer towards each other smoothly
	void Coherence(std::vector<BoidObject*>* boidsInRange)
	{
		positionAverage = Vector3f(0, 0, 0);
		for (int i = 0; i < boidsInRange->size(); i++)
			positionAverage = positionAverage + boidsInRange->at(i)->transform.Position;
		positionAverage.x /= boidsInRange->size();
		positionAverage.y /= boidsInRange->size();
		positionAverage.z /= boidsInRange->size();

		velocity.x += (positionAverage.x - transform.Position.x) * coherence;
		velocity.y += (positionAverage.y - transform.Position.y) * coherence;
		velocity.z += (positionAverage.z - transform.Position.z) * coherence;
	}

	bool InRange(BoidObject* boid)
	{
		if(std::sqrt(std::pow(boid->transform.Position.x - transform.Position.x, 2) + std::pow(boid->transform.Position.y - transform.Position.y, 2) + std::pow(boid->transform.Position.z - transform.Position.z, 2) < eyesightRange))
			return true;
		return false;
	}

	void GetBoidsInRange(std::vector<BoidObject*>& boidsInRange)
	{
		for (int i = 0; i < boids->size(); i++)
		{
			if (InRange(boids->at(i)))
				boidsInRange.push_back(boids->at(i));
		}
	}

	float eyesightRange = 12;
	float turnFactor = 0.01f;
	float boundingDistance = 20;
	
	float coherence = 0.0008f;
	float seperation = 0.00025f;
	float alighnment = 0.06f;

	double speed = 0.0f;
	double minSpeed = 0.4f;
	double maxSpeed = 1.0f;

	Vector3f positionAverage = Vector3f(0, 0, 0);
	Vector3f velocityAverage = Vector3f(0, 0, 0);
	Vector3f close = Vector3f(0, 0, 0);
	Vector3f velocity = Vector3f(0.01f, 0.01f, 0.01f);
};