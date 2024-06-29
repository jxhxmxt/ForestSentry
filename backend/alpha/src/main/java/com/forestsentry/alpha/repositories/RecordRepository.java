package com.forestsentry.alpha.repositories;

import java.util.UUID;

import org.springframework.data.jpa.repository.JpaRepository;

import com.forestsentry.alpha.models.entities.Record;

public interface RecordRepository extends JpaRepository<UUID, Record> {
    
}
