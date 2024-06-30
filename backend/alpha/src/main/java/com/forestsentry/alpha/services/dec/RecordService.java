package com.forestsentry.alpha.services.dec;

import java.util.UUID;
import java.util.List;

import org.springframework.data.domain.Page;

import com.forestsentry.alpha.models.dtos.RecordDTO;
import com.forestsentry.alpha.models.entities.Record;

public interface RecordService {
    public Boolean save(RecordDTO dto) throws Exception;
    public Boolean delete(UUID id) throws Exception;

    public Record findLatest() throws Exception;
    public Record findById(UUID id) throws Exception;
    public Page<Record> findByDeviceId(String id, Integer page, Integer size) throws Exception;
    public List<Record> findLatestByDeviceId(List<String> ids) throws Exception;
}